#ifndef TWITCHCONTROLLER_H
#define TWITCHCONTROLLER_H

#include <QObject>
#include <QStatusBar>
#include "twitch.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QUrlQuery>
#include <QJsonDocument>

class TwitchController : public QObject
{
    Q_OBJECT    // needed for signals/slots

private:
    /* UI */
    QStatusBar* console;
    Twitch* twitch;
    QLabel* id_label;
    QLabel* liveStatus_label;
    QLabel* streamTitle_label;

    /* Twitch API Info */
    QString clientID;
    QString clientSecret;
    unsigned int unhashed_state;
    QString accessToken;
    QString refreshToken;
    QString redirectURI;
    int requestType;

    /* User Info */
    QString userID;
    QString userLogin;

    /* Misc/Functions */
    QRandomGenerator generator;

    void setConsoleText(QString text, int duration = 10);
    void setRequestType(int request_type);
    void setUserLoginLabel();

    /* Functions below parse the network replies of the function named after "parse" from Twitch class */
    void parseGetAccessToken(QJsonDocument jsonDoc);
    void parseValidateAccessToken(QJsonDocument jsonDoc);

private slots:
    void parseJsonReply(QJsonDocument jsonDoc);

signals:
    void finished(bool status);

public:
    TwitchController();
    ~TwitchController();
    void setup(QStatusBar* statusBar, QLabel* id, QLabel* liveStatus, QLabel* streamTitle);
    QString getTwitchConnectURL();
    void validateRedirectURL(QString redirect_url);

    enum RequestType
    {
        getAccessToken,
        validateAccessToken
    };
};

#endif // TWITCHCONTROLLER_H
