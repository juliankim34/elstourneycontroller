#ifndef CHALLONGE_H
#define CHALLONGE_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class Challonge : public QObject
{
    Q_OBJECT    // needed for signal/slots

private:
    QString api_key;
    QNetworkAccessManager* manager;

private slots:
    void replyReceived(QNetworkReply* netReply);

signals:
    void returnData(QJsonArray data);

public:
    Challonge();
    ~Challonge();

    void setAPIKey(QString key);
    void getTournaments();  // no params needed
    void getMatches(QString tourney_id); // true for completed matches, false for in_progress
    void getParticipants(QString tourney_id);
    void updateMatches(QString tourney_id, QString match_id, QString score, QString winner = "");
    void reopenMatch(QString tourney_id, QString match_id);

};

#endif // CHALLONGE_H
