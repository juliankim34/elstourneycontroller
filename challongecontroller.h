#ifndef CHALLONGECONTROLLER_H
#define CHALLONGECONTROLLER_H

#include <QObject>
#include <QLabel>
#include <QListWidget>
#include "challonge.h"
#include <QString>
#include "tournamentlistwidgetitem.h"
#include "matchlistwidgetitem.h"
#include <QMap>
#include <QStatusBar>

#define TOURNAMENTS 0   // used in slots, should probably put this in an enum later
#define MATCHES 1
#define PARTICIPANTS 2
#define UPDATE 3
#define REOPEN 4

class ChallongeController : public QObject
{
    Q_OBJECT    // in order to use signals/slots

private:
    QStatusBar* console;
    QListWidget* currentListWidget;
    Challonge* challongeAPI;
    QMap<QString, QString> currentParticipants;
    QString currentTourneyID;
    int requestType;
    bool matchesStatus;

    void setRequestType(int request);
    void getParticipants(QString tourney_id);
    void parseMatches(QJsonValue player1_id, QJsonValue player2_id, QJsonObject innerObj, QString winnerID = "");

private slots:
    void replyReceived(QJsonArray data);
    void getMatches();  // in a slot because it has to execute after getParticipants() finishes
    void setConsoleText(QString text, int duration = 10);

signals:
    void finished();

public:
    ChallongeController();
    ~ChallongeController();

    void setAPIKey(QString api_key, QStatusBar *statusBar);
    void displayTournaments(QListWidget *widget);
    void displayMatches(QString tourney_id, QListWidget *widget, bool status); // true for completed matches, false for in_progress
    void updateMatch(QString tourney_id, QString match_id, QString score, QString winnerID);
    void reopenMatch(QString tourney_id, QString match_id);

};

#endif // CHALLONGECONTROLLER_H
