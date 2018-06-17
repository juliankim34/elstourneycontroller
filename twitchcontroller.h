#ifndef TWITCHCONTROLLER_H
#define TWITCHCONTROLLER_H

#include <QObject>
#include <QStatusBar>
#include "twitch.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QGroupBox>

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
    QGroupBox* twitchSection;

    /* Twitch API Info */
    QString clientID;
    QString clientSecret;
    unsigned int unhashed_state;
    QString accessToken;
    QString refreshToken;
    QString redirectURI;
    int requestType;
    bool refreshAttempted;

    /* User Info */
    QString userID;
    QString userLogin;
    QString streamID;

    /* Misc/Functions */
    QRandomGenerator generator;

    void setConsoleText(QString text, int duration = 10);
    void setRequestType(int request_type);
    void setUserLoginLabel();

    /* Functions below parse the network replies of the function named after "parse" from Twitch class */
    void parseGetAccessToken(QJsonDocument jsonDoc);
    void parseValidateAccessToken(QJsonDocument jsonDoc);
    void parseGetStreams(QJsonDocument jsonDoc);

    void refreshAccessToken();
    void parseRefreshAccessToken(QJsonDocument jsonDoc);
    void parseClipStream(QJsonDocument jsonDoc);

private slots:
    void parseJsonReply(QJsonDocument jsonDoc);
    void getStreamInfoSlot(bool validated);
    void clipStreamSlot(bool validated);

signals:
    void finished(bool status);

public:
    TwitchController();
    ~TwitchController();
    void setup(QStatusBar* statusBar, QLabel* id, QLabel* liveStatus, QLabel* streamTitle, QGroupBox *twitchBox);
    QString getTwitchConnectURL();
    void validateRedirectURL(QString redirect_url);
    void getStreamInfo();
    void signOut();
    void clipStream();
    //void refreshAccToken(); debugging func only

    enum RequestType
    {
        getAccessToken,
        validateAccessToken,
        getRefreshedAccessToken,
        getStreams,
        clipCurrentStream
    };
};

#endif // TWITCHCONTROLLER_H
