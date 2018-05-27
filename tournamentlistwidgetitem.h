#ifndef TOURNAMENTLISTWIDGETITEM_H
#define TOURNAMENTLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QString>


class TournamentListWidgetItem : public QListWidgetItem
{
public:
    TournamentListWidgetItem() = default; // should call QListWidgetItem() for me too

    void setInfo(QString tourney_name, QString tourney_id);
    void setToDefaultText();  // default will be tourney_name
    QString getTournamentName();
    QString getTournamentID();

private:
    QString tournament_name;
    QString tournament_id;
};

#endif // TOURNAMENTLISTWIDGETITEM_H
