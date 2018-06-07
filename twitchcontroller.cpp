#include "twitchcontroller.h"
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>

TwitchController::TwitchController()
    : twitch(new Twitch()), redirectURI("http://localhost")
{
    generator = QRandomGenerator::securelySeeded();
}

/* Public Functions Below */
TwitchController::~TwitchController()
{
    delete twitch;
}

void TwitchController::setup(QStatusBar *statusBar, QLabel* id, QLabel* liveStatus, QLabel *streamTitle)
{
    console = statusBar;
    id_label = id;
    liveStatus_label = liveStatus;
    streamTitle_label = streamTitle;
    // get clientID and clientSecret from file

    QFile client_id_file;
    QFile client_secret_file;

    client_id_file.setFileName(":/client_id.txt");
    client_secret_file.setFileName(":/client_secret.txt");

    client_id_file.open(QIODevice::ReadOnly);
    clientID = QString(client_id_file.readAll());
    client_id_file.close();

    client_secret_file.open(QIODevice::ReadOnly);
    clientSecret = QString(client_secret_file.readAll());
    client_secret_file.close();
}

QString TwitchController::getTwitchConnectURL()
{
    unhashed_state = generator.generate();

    return twitch->buildOAuthAuthenticateURL(clientID, redirectURI, QString::number(unhashed_state), "clips:edit");
}

void TwitchController::validateRedirectURL(QString redirect_url)
{
    qDebug() << redirect_url;
    QUrlQuery params = QUrlQuery((QUrl(redirect_url)));
    QString hashed_state;

    hashed_state = params.queryItemValue("state");
    //qDebug() << hashed_state;
    if (hashed_state.isEmpty() || !twitch->validateState(hashed_state, QString::number(unhashed_state)))
    {
        setConsoleText("Field 'state' is empty/incorrect! Please copy the ENTIRE redirect URL or try authorizing again.", 20);
        return;    // no state returned, do not continue processing
    }
    QString authCode = params.queryItemValue("code");

    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    setRequestType(TwitchController::getAccessToken);

    twitch->getAccessToken(clientID, clientSecret, authCode, redirectURI);
}


/* Public Functions End */

/* Private functions start */
void TwitchController::setConsoleText(QString text, int duration)
{
    console->showMessage(text, (duration * 1000));
}

void TwitchController::setRequestType(int request_type)
{
    requestType = request_type;
}

void TwitchController::setUserLoginLabel()
{
    if (userLogin.isEmpty())
        id_label->setText("User: N/A");
    else
        id_label->setText(QString("User: ") + userLogin);
}

void TwitchController::parseGetAccessToken(QJsonDocument jsonDoc)
{
    if (jsonDoc.isEmpty())
    {
        setConsoleText("Error: Empty reply when getting Twitch access token!");
        return;
    }
    QJsonObject json = jsonDoc.object();
    accessToken = json["access_token"].toString();
    refreshToken = json["refresh_token"].toString();
    qDebug() << QString("TwitchController::parseGetAccessToken - Access Token: ") + accessToken;
    qDebug() << QString("TwitchController::parseGetAccessToken - Refresh Token: ") + refreshToken;

    // Immediately Validate Access Token
    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    setRequestType(TwitchController::validateAccessToken);
    twitch->validateAccessToken(accessToken);
}

void TwitchController::parseValidateAccessToken(QJsonDocument jsonDoc)
{
    if (jsonDoc.isEmpty())
    {
        setConsoleText("Error: Empty reply when validating Twitch access token!");
        emit finished(false);
        return;
    }
    QJsonObject json = jsonDoc.object();
    userID = json["user_id"].toString();
    userLogin = json["login"].toString();
    setUserLoginLabel();
    setConsoleText("Access Token successfully validated.", 20);
    emit finished(true);
}

/* Private functions end */

/* Private slots */
void TwitchController::parseJsonReply(QJsonDocument jsonDoc)
{
    QObject::disconnect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    switch (requestType)
    {
    case TwitchController::getAccessToken:
        parseGetAccessToken(jsonDoc);
        break;
    case TwitchController::validateAccessToken:
        parseValidateAccessToken(jsonDoc);
        break;
    default:
        qDebug() << "Unsupported requestType";
        break;
    }
}
