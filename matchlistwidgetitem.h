#ifndef MATCHLISTWIDGETITEM_H
#define MATCHLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QString>

class MatchListWidgetItem : public QListWidgetItem
{
public:
    MatchListWidgetItem() = default; // should call QListWidgetItem() for me

    void setInfo(QString tourneyID, QString matchID, QString p1, QString p1_id, QString p2, QString p2_id, QString score, QString round_num, QString winnerID = "");
    void setToDefaultText();  // default will "p1 vs. p2"
    QString getmatchID();
    QString getP1();
    QString getP1ID();
    QString getP2();
    QString getP2ID();
    QString getScore();
    QString getTourneyID();
    QString getRound();
    QString getWinnerID();


private:
    QString match_id;
    QString player1;
    QString player2;
    QString player1_id;
    QString player2_id;
    QString currentScore;
    QString tourney_id;
    QString round;
    QString winner_id;
};

#endif // MATCHLISTWIDGETITEM_H
