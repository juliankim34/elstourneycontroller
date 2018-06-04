#ifndef ELSCONTROLLER_H
#define ELSCONTROLLER_H

#include <QMainWindow>
#include <QString>
#include <QMenu>
#include "mapmanager.h"
#include "filemanager.h"
#include "challongecontroller.h"

namespace Ui {
class elscontroller;
}

class elscontroller : public QMainWindow
{
    Q_OBJECT

public:
    explicit elscontroller(QWidget *parent = 0);
    ~elscontroller();

    void setConsoleText(QString text, int duration = 0);  // for use by other controllers

private slots:
    void on_pickMapButton_clicked();

    void on_updateButton_clicked();

    void on_challongeSignInButton_clicked();

    void on_apiLineEdit_textChanged(const QString &arg1);

    void on_challongeSelectButton_clicked();

    void on_challongeSignOutButton_clicked();

    void on_challongeBackButton_clicked();

    void on_challongeRefreshButton_clicked();

    void on_challongeSubmitButton_clicked();

    void on_updateScoreboardButton_clicked();

    void on_challongeSubmitUpdateButton_clicked();

    void on_p1WinnerCheckBox_stateChanged(int arg1);

    void on_p2WinnerCheckBox_stateChanged(int arg1);

    void on_swapSidesButton_clicked();

    void displayAboutWindow();

    void openWikiInDefaultBrowser();

    void openSourceInDefaultBrowser();

    void on_p1CopyNameButton_clicked();

    void on_p2CopyNameButton_clicked();

    void on_completedMatchesButton_clicked();

    void on_reopenMatchButton_clicked();
/*
    void on_copyButtonMsg1_clicked();

    void on_copyButtonMsg2_clicked();

    void on_copyButtonMsg3_clicked();
*/
private:
    /* UI Basic */
    Ui::elscontroller *ui;
    QMenu* helpMenu;
    void setupMenuBar();

    /* Scoreboard HUD Tab */
    FileManager file_manager;
    MapManager map_manager;
    void displayMaps();

    /* Challonge Tab */
    ChallongeController challonge_manager;
    bool tournamentsMode; // needed to determine behavior of select/refresh buttons FIXME?
    bool matchesShown;      // true - completed     false - in_progress
    QString currentTourneyID; // needed for refresh button FIXME?
    MatchListWidgetItem* currentMatch;  // needed for submit button FIXME?
    QClipboard *clipboard;
    void showChallongeUI(bool login, bool tournaments, bool matches);
    void hideAllChallongeUI();
    void clearMatchInfoScreen();
    void setMatch(QString p1, QString p2, QString round, QString score, QString tourney_id);
    void copyTextToClipBoard(QString text);
};

#endif // ELSCONTROLLER_H
