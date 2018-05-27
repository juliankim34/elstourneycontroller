#include "matchlistwidgetitem.h"
#include <QDebug>

void MatchListWidgetItem::setInfo(QString tourneyID, QString matchID, QString p1, QString p1_id, QString p2, QString p2_id, QString score, QString round_num)
{
    match_id = matchID;
    player1 = p1;
    player1_id = p1_id;
    player2 = p2;
    player2_id = p2_id;
    currentScore = score;
    tourney_id = tourneyID;
    round = round_num;
}

void MatchListWidgetItem::setToDefaultText()
{
    if (player1.isEmpty() || player2.isEmpty())
    {
        qDebug() << "One or both of the players are empty strings";
        setText("Empty Match (should not happen)");
    }
    else
    {
        QString match = player1 + " vs. " + player2;
        setText(match);
    }
}

QString MatchListWidgetItem::getmatchID()
{
    return match_id;
}

QString MatchListWidgetItem::getP1()
{
    return player1;
}

QString MatchListWidgetItem::getP1ID()
{
    return player1_id;
}

QString MatchListWidgetItem::getP2()
{
    return player2;
}

QString MatchListWidgetItem::getP2ID()
{
    return player2_id;
}

QString MatchListWidgetItem::getScore()
{
    return currentScore;
}

QString MatchListWidgetItem::getTourneyID()
{
    return tourney_id;
}

QString MatchListWidgetItem::getRound()
{
    return round;
}
