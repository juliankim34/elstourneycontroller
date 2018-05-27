#include "challongecontroller.h"
#include <QJsonObject>

ChallongeController::ChallongeController()
    : challongeAPI(new Challonge()), console(nullptr), currentListWidget(nullptr), currentParticipants()
{
}

ChallongeController::~ChallongeController()
{
    delete challongeAPI;
}

/* Public Functions Below */
void ChallongeController::setAPIKey(QString api_key, QStatusBar* statusBar)
{
    challongeAPI->setAPIKey(api_key);    // do not keep track of api_key, only pass it to Challonge who keeps the key private
    console = statusBar;
}

void ChallongeController::displayTournaments(QListWidget* widget)
{
    QObject::connect(challongeAPI, SIGNAL(returnData(QJsonArray)), this, SLOT(replyReceived(QJsonArray)));
    setRequestType(TOURNAMENTS);
    currentListWidget = widget;
    setConsoleText("Fetching tournaments from Challonge API...");
    challongeAPI->getTournaments(); // will emit returnData(QJsonArray)
}

void ChallongeController::displayMatches(QString tourney_id, QListWidget *widget)
{
    QObject::connect(this, SIGNAL(finished()), this, SLOT(getMatches()));
    setConsoleText("Fetching matches from Challonge API...");
    currentListWidget = widget;
    currentTourneyID = tourney_id;
    getParticipants(tourney_id);    // get this first so we can display the matches as player1_name vs. player2_name and not p1_id vs. p2_id
}

void ChallongeController::updateMatch(QString tourney_id, QString match_id, QString score, QString winnerID) // score format must be "1-1", "1-0", etc, FIXME later
{
    QObject::connect(challongeAPI, SIGNAL(returnData(QJsonArray)), this, SLOT(replyReceived(QJsonArray)));
    setRequestType(UPDATE);
    setConsoleText("Submitting score to Challonge...");
    challongeAPI->updateMatches(tourney_id, match_id, score, winnerID);
}

/* Private functions */
void ChallongeController::setRequestType(int request)
{
    requestType = request;
}

void ChallongeController::getParticipants(QString tourney_id)
{
    QObject::connect(challongeAPI, SIGNAL(returnData(QJsonArray)), this, SLOT(replyReceived(QJsonArray)));
    setRequestType(PARTICIPANTS);
    challongeAPI->getParticipants(tourney_id);
}

void ChallongeController::setConsoleText(QString text, int duration)
{
    console->showMessage(text, (duration * 1000));
}

/* Slots */
void ChallongeController::replyReceived(QJsonArray data)
{
    QObject::disconnect(challongeAPI, SIGNAL(returnData(QJsonArray)), this, SLOT(replyReceived(QJsonArray)));
    if (data.isEmpty() && requestType != UPDATE)
    {
        setConsoleText("Oops, something went wrong! API Call did not return any data. Check your API Key and/or network connection.", 20);
        return;
    }
    switch (requestType)
    {
    case TOURNAMENTS:
        currentListWidget->clear();
        for (int i = 0; i < data.size(); ++i)
        {
            QJsonObject outerObj = data[i].toObject();
            QJsonObject innerObj = outerObj["tournament"].toObject();
            QString tourneyName = innerObj["name"].toString();
            QString tourneyID = innerObj["url"].toString();

            TournamentListWidgetItem* toAdd = new TournamentListWidgetItem();
            toAdd->setInfo(tourneyName, tourneyID);
            toAdd->setToDefaultText();
            currentListWidget->addItem(toAdd);
        }
        setConsoleText("Fetch tournaments succeeded. If you do not see your tournament, please \"Start\" it first. If you see done tournaments, please \"End\" it.", 20);
    break;
    case MATCHES:
        currentListWidget->clear();
        for (int i = 0; i < data.size(); ++i)
        {
            QJsonObject outerObj = data[i].toObject();
            QJsonObject innerObj = outerObj["match"].toObject();
            QJsonValue player1_id = innerObj["player1_id"];
            QJsonValue player2_id = innerObj["player2_id"];
            QJsonValue winner = innerObj["winner_id"];

            if (player1_id != QJsonValue::Null && player2_id != QJsonValue::Null && winner == QJsonValue::Null)
            {
                QString p1ID = QString::number(player1_id.toInt());
                QString p2ID = QString::number(player2_id.toInt());
                auto p1Name = currentParticipants.find(p1ID);   // this find should not fail unless someone deletes a participant extremely fast mid API call...
                auto p2Name = currentParticipants.find(p2ID);
                QString matchID = QString::number(innerObj["id"].toInt());
                QString score = innerObj["scores_csv"].toString();
                QString round = QString::number(innerObj["round"].toInt());

                MatchListWidgetItem* toAdd = new MatchListWidgetItem();
                toAdd->setInfo(currentTourneyID, matchID, p1Name.value(), p1ID, p2Name.value(), p2ID, score, round);
                toAdd->setToDefaultText();
                currentListWidget->addItem(toAdd);
            }
        }
        setConsoleText("Fetch matches succeeded. Only in-progress matches are shown (i.e. no winner declared).");
    break;
    case PARTICIPANTS:
        currentParticipants.clear();
        for (int i = 0; i < data.size(); ++i)
        {
            QJsonObject outerObj = data[i].toObject();
            QJsonObject innerObj = outerObj["participant"].toObject();
            QString participant_name = innerObj["display_name"].toString();
            QString participant_id = QString::number(innerObj["id"].toInt());

            currentParticipants.insert(participant_id, participant_name);
        }
    break;
    case UPDATE:
        setConsoleText("Results submitted to Challonge.");  // nothing necessary to process
    break;
    default:
        qDebug() << "Unrecognized requestType";
    break;
    }

    emit finished();    // in case anyone wants to chain this to another slot
}

void ChallongeController::getMatches()
{
    QObject::disconnect(this, SIGNAL(finished()), this, SLOT(getMatches()));
    QObject::connect(challongeAPI, SIGNAL(returnData(QJsonArray)), this, SLOT(replyReceived(QJsonArray)));
    setRequestType(MATCHES);
    challongeAPI->getMatches(currentTourneyID);   // currentTourneyID should be set to tourney_id
}
