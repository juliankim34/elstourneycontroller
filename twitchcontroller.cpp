#include "twitchcontroller.h"
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QDesktopServices>

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

void TwitchController::setup(QStatusBar *statusBar, QLabel* id, QLabel* liveStatus, QLabel *streamTitle, QGroupBox* twitchBox)
{
    console = statusBar;
    id_label = id;
    liveStatus_label = liveStatus;
    streamTitle_label = streamTitle;
    refreshAttempted = false;
    twitchSection = twitchBox;
    twitchSection->setEnabled(false);
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

void TwitchController::getStreamInfo()
{
    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument))); // signal for validateAccessToken
    QObject::connect(this, SIGNAL(finished(bool)), this, SLOT(getStreamInfoSlot(bool))); // signal for actual getStreamInfo request
    setRequestType(TwitchController::validateAccessToken);

    twitch->validateAccessToken(accessToken);
}

void TwitchController::signOut()
{
    twitchSection->setEnabled(false);
    userID.clear();
    userLogin.clear();
    liveStatus_label->setText("Live: N/A");
    id_label->setText("User: N/A");
    streamTitle_label->setText("Stream Title: N/A");
    setConsoleText("Signed out of Twitch.");
}

void TwitchController::clipStream()
{
    if (liveStatus_label->text() != QString("Live: Yes"))
    {
        setConsoleText("You are not live! Refresh stream info to detect stream.");
        return;
    }
    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument))); // signal for validateAccessToken
    QObject::connect(this, SIGNAL(finished(bool)), this, SLOT(clipStreamSlot(bool)));   // signal for actual clipStream() request
    setRequestType(TwitchController::validateAccessToken);

    twitch->validateAccessToken(accessToken);
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
    //qDebug() << userLogin + QString(" - ") + userID;
    //setUserLoginLabel();
    setConsoleText("Access Token successfully validated.", 20);
    twitchSection->setEnabled(true);
    emit finished(true);
}

void TwitchController::parseGetStreams(QJsonDocument jsonDoc)
{
    if (jsonDoc.isEmpty())
    {
        setConsoleText("Error: Empty reply when fetching stream info! Don't spam this button!");
        return;
    }
    //QJsonObject json = jsonDoc.object();
    QJsonArray data = jsonDoc["data"].toArray();
    setUserLoginLabel();
    if (data.isEmpty())
    {
        liveStatus_label->setText("Live: No");
        streamTitle_label->setText("Stream Title: N/A");
        setConsoleText("Found user. Give Twitch ~5 min to update your live status if it says you're offline. Do NOT spam this button. Twitch will spam block you.", 30);
        return;
    }
    QJsonObject stream = data[0].toObject(); // we are searching by 1 user_id, therefore impossible to have array size > 1
    QString title = stream["title"].toString();
    QString status = stream["type"].toString();
    streamID = stream["id"].toString();

    streamTitle_label->setText(QString("Stream Title: ") + title);
    liveStatus_label->setText((status == QString("live") ? "Live: Yes" : "Live: No"));
    setConsoleText("User and stream found. Everything all set! If you see this after you ended stream, give Twitch ~5 min to update your live status.", 30);

}

void TwitchController::refreshAccessToken()
{
    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    setRequestType(TwitchController::getRefreshedAccessToken);
    twitch->refreshAccessToken(clientID, clientSecret, refreshToken);
}

void TwitchController::parseRefreshAccessToken(QJsonDocument jsonDoc)
{
    if (jsonDoc.isEmpty() || jsonDoc["error"] != QJsonValue::Undefined)
    {
        emit finished(false);   // failed
        return;
    }
    setConsoleText("Access Token successfully refreshed.");
    accessToken = jsonDoc["access_token"].toString();
    refreshToken = jsonDoc["refresh_token"].toString();

    // immediately validate the new access token
    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    setRequestType(TwitchController::validateAccessToken);
    twitch->validateAccessToken(accessToken);
}

void TwitchController::parseClipStream(QJsonDocument jsonDoc)
{
    if (jsonDoc.isEmpty())
    {
        setConsoleText("Error: Clip creation did not return back clip URL. Please try again.");
        return;
    }
    QJsonArray data = jsonDoc["data"].toArray();
    if (data.isEmpty())
    {
        setConsoleText("Error: Data field is empty for clip creation (this should not happen). Please try again.");
        return;
    }
    QJsonObject clip = data[0].toObject();  // only one object
    QString url = clip["edit_url"].toString();

    QDesktopServices::openUrl(QUrl(url));
    setConsoleText("Clip created. Please do NOT spam clip creation as Twitch imposes rate limits. Clip button disabled for 5 sec.", 0);
}

/* Private functions end */

/* Private slots */
void TwitchController::parseJsonReply(QJsonDocument jsonDoc)
{
    QObject::disconnect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    switch (requestType)
    {
    case TwitchController::getAccessToken:
        qDebug() << jsonDoc.object();
        parseGetAccessToken(jsonDoc);
        break;
    case TwitchController::validateAccessToken:
        parseValidateAccessToken(jsonDoc);
        break;
    case TwitchController::getStreams:
        qDebug() << "TwitchController::getStreams";
        qDebug() << jsonDoc.object();
        parseGetStreams(jsonDoc);
        break;
    case TwitchController::getRefreshedAccessToken:
        qDebug() << "TwitchController::getRefreshedAccessToken";
        qDebug() << jsonDoc.object();
        parseRefreshAccessToken(jsonDoc);
        break;
    case TwitchController::clipCurrentStream:
        parseClipStream(jsonDoc);
        break;
    default:
        qDebug() << "Unsupported requestType - " + QString::number(requestType);
        break;
    }
}

void TwitchController::getStreamInfoSlot(bool validated)
{
    QObject::disconnect(this, SIGNAL(finished(bool)), this, SLOT(getStreamInfoSlot(bool)));
    if (!validated) // token is not valid
    {
        if (refreshAttempted)   // do not attempt to refresh twice or get stuck in a loop
        {
            setConsoleText("Fatal Error: Access Token is not valid and could not be refreshed. Please re-authorize your Twitch account.");
            signOut();
            return;
        }
        setConsoleText("Error: Access Token not valid! Attempting to refresh token...");
        refreshAttempted = true;
        QObject::connect(this, SIGNAL(finished(bool)), this, SLOT(getStreamInfoSlot(bool)));    // this function
        refreshAccessToken();
        return;
    }
    refreshAttempted = false;
    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    setRequestType(TwitchController::getStreams);
    setConsoleText("Fetching stream info..");
    twitch->getStreams(clientID, userLogin);
}

void TwitchController::clipStreamSlot(bool validated)
{
    QObject::disconnect(this, SIGNAL(finished(bool)), this, SLOT(clipStreamSlot(bool)));
    if (!validated) // token is not valid
    {
        if (refreshAttempted)   // do not attempt to refresh twice or get stuck in a loop
        {
            setConsoleText("Fatal Error: Access Token is not valid and could not be refreshed. Please re-authorize your Twitch account.");
            signOut();
            return;
        }
        setConsoleText("Error: Access Token not valid! Attempting to refresh token...");
        refreshAttempted = true;
        QObject::connect(this, SIGNAL(finished(bool)), this, SLOT(clipStreamSlot(bool)));   // this function
        refreshAccessToken();
        return;
    }
    refreshAttempted = false;
    QObject::connect(twitch, SIGNAL(returnData(QJsonDocument)), this, SLOT(parseJsonReply(QJsonDocument)));
    setRequestType(TwitchController::clipCurrentStream);
    setConsoleText("Creating clip. Please be patient as this takes time...");
    twitch->createClip(clientID, streamID);
}
