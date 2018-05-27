#include "tournamentlistwidgetitem.h"
#include <QDebug>

void TournamentListWidgetItem::setInfo(QString tourney_name, QString tourney_id)
{
    tournament_name = tourney_name;
    tournament_id = tourney_id;
}

void TournamentListWidgetItem::setToDefaultText()
{
    if (tournament_name.isEmpty())
    {
        qDebug() << "No tournament_name supplied";
        setText("Unnamed Tournament");
    }
    else
    {
        setText(tournament_name);
    }
}

QString TournamentListWidgetItem::getTournamentID()
{
    return tournament_id;
}

QString TournamentListWidgetItem::getTournamentName()
{
    return tournament_name;
}
