#include "twitch.h"
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QByteArray>

Twitch::Twitch()
{
    manager = new QNetworkAccessManager(this);
}

Twitch::~Twitch()
{
    delete manager;
}

/* Public Functions Below */
QString Twitch::buildOAuthAuthenticateURL(QString clientID, QString redirectURI, QString unhashed_state, QString scopes) // space separated list of scopes
{
    QString request = "https://id.twitch.tv/oauth2/authorize";
    QUrl url(request);
    QUrlQuery params;

    params.addQueryItem("client_id", clientID);
    params.addQueryItem("redirect_uri", redirectURI);
    params.addQueryItem("response_type", "code");
    params.addQueryItem("scope", scopes);
    params.addQueryItem("force_verify", "true");

    // hash the unhashed_state
    //qDebug() << unhashed_state;
    QString hash_state = QString(QCryptographicHash::hash(unhashed_state.toUtf8(), QCryptographicHash::Sha256).toHex());
    //qDebug() << hash_state;
    params.addQueryItem("state", hash_state);

    url.setQuery(params);
    qDebug() << "Twitch::buildOAuthAuthenticateURL " + url.toString();
    return url.toString();
}

bool Twitch::validateState(QString state, QString unhashed_state)  // true if state is valid, else false
{
    // validate that hashed(unhashed_state) = state returned
    QString expected_state = QString(QCryptographicHash::hash(unhashed_state.toUtf8(), QCryptographicHash::Sha256).toHex());

    if (expected_state == state)
        return true;
    return false;
}

void Twitch::getAccessToken(QString clientID, QString clientSecret, QString authCode, QString redirectURI)
{
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://id.twitch.tv/oauth2/token";
    QUrl url(request);
    QUrlQuery params;

    params.addQueryItem("client_id", clientID);
    params.addQueryItem("client_secret", clientSecret);
    params.addQueryItem("code", authCode);
    params.addQueryItem("grant_type", "authorization_code"); // hardcode this
    params.addQueryItem("redirect_uri", redirectURI);
    url.setQuery(params);
    qDebug() << "Twitch::getAccessToken " + url.toString();

    QNetworkRequest netRequest(url);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/x-www-form-urlencoded")); // needed?

    manager->post(netRequest, QByteArray());   // do not need any payload
}

void Twitch::validateAccessToken(QString accessToken)
{
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://id.twitch.tv/oauth2/validate";
    QUrl url(request);
    qDebug() << "Twitch::validateAccessToken " + url.toString();

    QNetworkRequest netRequest(url);
    QString header_payload = QString("OAuth ") + accessToken;
    netRequest.setRawHeader(QByteArray("Authorization"), header_payload.toUtf8());
    manager->get(netRequest);
}

void Twitch::refreshAccessToken(QString clientID, QString clientSecret, QString refreshToken)
{
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://id.twitch.tv/oauth2/token";
    QUrl url(request);
    qDebug() << "Twitch::refreshAccessToken " + url.toString();

    QNetworkRequest netRequest(url);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/x-www-form-urlencoded"));

    QString payload = QString("?grant_type=refresh_token&refresh_token=") + refreshToken + QString("&client_id=") + clientID + QString("&client_secret=") + clientSecret;
    QUrl payload_encoded(payload);  // url encode the payload because tokens not guaranteed to be url safe
    qDebug() << payload_encoded.toString();

    manager->post(netRequest, payload_encoded.toString().toUtf8());
}

void Twitch::getStreams(QString clientID, QString userID)   // only accept userID
{
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://api.twitch.tv/helix/streams?user_id" + userID;
    QUrl url(request);
    qDebug() << "Twitch::getStreams " + url.toString();

    QNetworkRequest netRequest(url);
    netRequest.setRawHeader(QByteArray("Client-ID"), clientID.toUtf8());
    manager->get(netRequest);
}

void Twitch::createClip(QString clientID, QString streamID)
{
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://api.twitch.tv/helix/clips";
    QUrl url(request);
    QUrlQuery params;

    params.addQueryItem("broadcaster_id", streamID);
    params.addQueryItem("has_delay", "true");
    url.setQuery(params);
    qDebug() << "Twitch::createClip " + url.toString();

    QNetworkRequest netRequest(url);
    QString header_payload = QString("Bearer ") + clientID;
    netRequest.setRawHeader(QByteArray("Authorization"), header_payload.toUtf8());
    manager->post(netRequest, QByteArray()); // no payload
}

/* Public Functions End */

/* Private slot(s) begin */
void Twitch::replyReceived(QNetworkReply *netReply)
{
    QObject::disconnect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*))); // do not process anything else
    netReply->deleteLater();
    QByteArray* buffer = new QByteArray();
    QJsonDocument jsonDoc;

    if (netReply->error() == QNetworkReply::NoError)
    {
        buffer->append(netReply->readAll());
        jsonDoc = QJsonDocument::fromJson(*buffer);
        buffer->clear();
        //qDebug() << "Twitch::replyReceived\n" + QString(jsonDoc.toBinaryData());
    }
    else
    {
        qDebug() << netReply->errorString();
    }
    delete buffer;
    emit returnData(jsonDoc);   // whoever used this class to make a network request MUST catch this signal to receieve the data
}

/* Private slot(s) end */
