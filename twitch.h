#ifndef TWITCH_H
#define TWITCH_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCryptographicHash>   // protect against CSRF attacks

class Twitch : public QObject
{
    Q_OBJECT    // needed for signals/slots

private:
    QNetworkAccessManager* manager;

private slots:
    void replyReceived(QNetworkReply* netReply);

signals:
    void returnData(QJsonDocument data);

public:
    Twitch();
    ~Twitch();

    QString buildOAuthAuthenticateURL(QString clientID, QString redirectURI, QString unhashed_state, QString scopes);
    bool validateState(QString state, QString unhashed_state);
    void validateAccessToken(QString accessToken);
    void refreshAccessToken(QString clientID, QString clientSecret, QString refreshToken);
    void getAccessToken(QString clientID, QString clientSecret, QString authCode, QString redirectURI);
    void getStreams(QString clientID, QString userID);
    void createClip(QString clientID, QString streamID);
};

#endif // TWITCH_H
