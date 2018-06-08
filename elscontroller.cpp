#include "elscontroller.h"
#include "ui_elscontroller.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QtAlgorithms>
#include <QClipboard>

elscontroller::elscontroller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::elscontroller),
    challonge_manager(),
    currentMatch(nullptr),
    timer(new QTimer())
{
    /* UI setup */
    ui->setupUi(this);
    setupMenuBar();

    /* Prep for files */
    file_manager.setupFiles();
    map_manager.setupFile();

    /* Add Initial UI Elements */
    ui->statusbar->showMessage("Welcome to the Elsword Tournament Controller by Synai!");
    displayMaps();
    showChallongeUI(true, false, false); // login screen
    ui->mainTabWidget->setCurrentIndex(0);

    /* Misc */
    clipboard = QApplication::clipboard();
    twitch_manager.setup(ui->statusbar, ui->twitchIDLabel, ui->twitchLiveLabel, ui->twitchStreamTitleLabel, ui->twitchSectionGroupBox);
}

elscontroller::~elscontroller()
{
    delete ui;
    //if (currentMatch != nullptr) // not needed because deleting ui will delete the listWidget which deletes the contents in it (which this points to) (?)
        //delete currentMatch;
    qDeleteAll(helpMenu->actions()); // guaranteed to have items due to constructor
    delete helpMenu;    // guaranteed to not be nullptr due to constructor
    delete timer;
    //delete clipboard; // generates compiler error? maybe it's RAII
}

/* Public Functions */
void elscontroller::setConsoleText(QString text, int duration) // duration in seconds, default to 0
{
    ui->statusbar->showMessage(text, (duration * 1000)); // timeout is in milliseconds
}

/* Private functions */
void elscontroller::displayMaps()
{
    map_manager.addMapsToListWidget(ui->mapListWidget);
}

/* Small section of Private Slots For Menu */
void elscontroller::displayAboutWindow()
{
    QMessageBox::about(NULL, "About", "Elsword Tournament Controller by Synai\t\n\t  Made with Qt 5.10.1\t\n\t  License: LGPL v3\t");
}

void elscontroller::openWikiInDefaultBrowser()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Synai/elstourneycontroller/wiki"));
}

void elscontroller::openSourceInDefaultBrowser()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Synai/elstourneycontroller"));
}

/* End section of private slots */

void elscontroller::setupMenuBar()
{
    helpMenu = ui->menubar->addMenu(QString("Help"));

    helpMenu->addAction("About", this, SLOT(displayAboutWindow()));
    helpMenu->addSeparator();
    helpMenu->addAction("View Online Wiki", this, SLOT(openWikiInDefaultBrowser()));
    helpMenu->addAction("Visit GitHub Link", this, SLOT(openSourceInDefaultBrowser()));
}

void elscontroller::hideAllChallongeUI() // also clear out contents
{
    /* Login */
    ui->apiLineEdit->hide();
    ui->challongeDescriptionLabel->hide();
    ui->challongeSignInButton->hide();
    /* Tournaments/Match Selection */
    ui->tournamentListWidget->hide();
    ui->challongeRefreshButton->hide();
    ui->challongeSelectButton->hide();
    ui->challongeSignOutButton->hide();
    ui->challongeBackButton->hide();
    ui->tournamentListWidget->clear();
    ui->completedMatchesButton->hide();
    ui->completedMatchesButton->hide();
    ui->reopenMatchButton->hide();
    ui->completedMatchesButton->setEnabled(false);
    ui->reopenMatchButton->setEnabled(false);
    /* Match Edit Screen */
    ui->matchGroupBox->setEnabled(false);
}

void elscontroller::showChallongeUI(bool login, bool tournaments, bool matches)
{
    hideAllChallongeUI();
    if (login)
    {
        ui->apiLineEdit->show();
        ui->challongeDescriptionLabel->setText("Challonge API Key:");
        ui->challongeDescriptionLabel->show();
        ui->challongeSignInButton->setEnabled(false);
        ui->challongeSignInButton->show();
        clearMatchInfoScreen();
    }
    else if (tournaments || matches)
    {
        ui->tournamentListWidget->show();
        ui->challongeRefreshButton->show();
        ui->challongeSelectButton->show();
        ui->challongeSignOutButton->show();
        ui->challongeBackButton->show();
        ui->challongeDescriptionLabel->show();
        ui->completedMatchesButton->show();
        ui->challongeDescriptionLabel->setText("Select a Tournament/Match:");
        ui->challongeBackButton->setEnabled(false);
        tournamentsMode = true;
        ui->completedMatchesButton->show();
        ui->reopenMatchButton->show();
    }
}

void elscontroller::clearMatchInfoScreen()
{
    ui->matchP1Label->setText("Player1");
    ui->matchP2Label->setText("Player2");
    ui->roundLabel->setText("Round 0");
    ui->challongeP1SpinBox->setValue(0);
    ui->challongeP2SpinBox->setValue(0);
    ui->p1WinnerCheckBox->setChecked(false);
    ui->p2WinnerCheckBox->setChecked(false);
}

void elscontroller::setMatch(QString p1, QString p2, QString round, QString score, QString tourney_id)
{
    QStringList scores;
    ui->matchP1Label->setText(p1);
    ui->matchP2Label->setText(p2);
    QString tourney_embedded_url = "<a href=\"https://challonge.com/" + tourney_id + "\">" + round + "</a>";
    ui->roundLabel->setText(tourney_embedded_url);
    ui->roundLabel->setTextFormat(Qt::RichText);
    ui->roundLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->roundLabel->setOpenExternalLinks(true);
    // Do annoying checks to deal with potential negative values... can't even use regex LOL
    int count = score.count("-");
    if (count == 1)    // score is of "0-0" format, ez best format
    {
        scores = score.split("-", QString::SkipEmptyParts);
    }
    else if (count == 2) // score is of "-1-1" or "1--1" format... "1-1-" is impossible
    {
        if (score.indexOf("-") == 0)    // format is "-1-1", "-12-1", "-12-30"
        {
            int divisionIndex = score.indexOf("-", 1); // find the next division, guaranteed to be the actual divisor
            scores.append(score.left(divisionIndex)); // p1
            scores.append(score.right(score.size() - divisionIndex - 1)); // p2
        }
        else                            // format is "1--1", "10--1", etc, "10-1-" is impossible
        {
            int divisionIndex = score.indexOf("-");
            scores.append(score.left(divisionIndex));
            scores.append(score.right(score.size() - divisionIndex - 1));
        }
    }
    else                                // format is "-1--1" LOL
    {
            int divisionIndex = score.indexOf("-", 1); // find the next division, guaranteed to be the actual divisor
            scores.append(score.left(divisionIndex));
            scores.append(score.right(score.size() - divisionIndex - 1));
    }
    if (scores.size() < 2)
    {
        qDebug() << "scores size is less than 2, return";
        return;
    }
    ui->challongeP1SpinBox->setValue(scores[0].toInt());
    ui->challongeP2SpinBox->setValue(scores[1].toInt());
}

void elscontroller::copyTextToClipBoard(QString text)
{
    clipboard->setText(text);
    setConsoleText("Copied to clipboard.", 5);
}

/* Slots */
void elscontroller::on_pickMapButton_clicked()
{
    ui->mapResultLabel->setText(map_manager.pickRandomMap(ui->mapListWidget));
}

void elscontroller::on_updateButton_clicked()
{
    QString p1 = ui->p1LineEdit->text();
    QString p2 = ui->p2LineEdit->text();
    QString p1_score = QString::number(ui->p1SpinBox->value());
    QString p2_score = QString::number(ui->p2SpinBox->value());
    QString info_1 = ui->file1LineEdit->text();
    QString info_2 = ui->file2LineEdit->text();
    QString info_3 = ui->file3LineEdit->text();

    if (file_manager.writeGameInfo(p1, p2, p1_score, p2_score, info_1, info_2, info_3))
    {
        setConsoleText("One or more files were not updated successfully.");
        return;
    }
    setConsoleText("Files Updated Successfully.", 5);
}

void elscontroller::on_challongeSignInButton_clicked()
{
    QString api_key = ui->apiLineEdit->text();
    challonge_manager.setAPIKey(api_key.simplified(), ui->statusbar); // strip whitespaces
    challonge_manager.displayTournaments(ui->tournamentListWidget);
    showChallongeUI(false, true, false); // tournaments screen
    ui->apiLineEdit->clear();
}

void elscontroller::on_apiLineEdit_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty())
        ui->challongeSignInButton->setEnabled(true);
    else
        ui->challongeSignInButton->setEnabled(false);
}

void elscontroller::on_challongeSelectButton_clicked()
{
    if (ui->tournamentListWidget->currentItem() == nullptr)
    {
        setConsoleText("Nothing selected!");
        return;
    }
    if (tournamentsMode)
    {
        TournamentListWidgetItem* selectedTournament = static_cast<TournamentListWidgetItem*>(ui->tournamentListWidget->currentItem()); // cast from ListWidgetItem*
        currentTourneyID = selectedTournament->getTournamentID();
        challonge_manager.displayMatches(currentTourneyID, ui->tournamentListWidget, false);    // always show in_progress only
        tournamentsMode = false;
        ui->challongeBackButton->setEnabled(true);
        ui->completedMatchesButton->setEnabled(true);
        ui->completedMatchesButton->setText("View Done");
        matchesShown = false;
    }
    else // update match info box
    {
        MatchListWidgetItem* selectedMatch = static_cast<MatchListWidgetItem*>(ui->tournamentListWidget->currentItem());    // cast from ListWidgetItem*
        currentMatch = selectedMatch;
        QString p1 = selectedMatch->getP1();
        QString p2 = selectedMatch->getP2();
        QString round = "Round " + selectedMatch->getRound();
        QString score = selectedMatch->getScore();
        setMatch(p1, p2, round, score, selectedMatch->getTourneyID());
        ui->p1WinnerCheckBox->setChecked(false);
        ui->p2WinnerCheckBox->setChecked(false);
        if (!matchesShown)   // viewing in-progress
        {
            ui->matchGroupBox->setEnabled(true);
            ui->challongeSubmitButton->setEnabled(true); // for some reason setEnabled on matchGroupBox is not recursively applying it to the buttons
            ui->challongeSubmitUpdateButton->setEnabled(true);
        }
        else
        {
            // don't enable anything
            QString winnerID = selectedMatch->getWinnerID();
            if (winnerID == selectedMatch->getP1ID())
                ui->p1WinnerCheckBox->setChecked(true);
            else if (winnerID == selectedMatch->getP2ID())
                ui->p2WinnerCheckBox->setChecked(true);
            else
                qDebug() << "winnerID from selectedMatch did not match P1ID or P2ID";
        }
    }
}

void elscontroller::on_challongeSignOutButton_clicked()
{
    showChallongeUI(true, false, false);
    setConsoleText("Signed out of Challonge.", 10);
}

void elscontroller::on_challongeBackButton_clicked() // this back button is only clickable to move from match selection -> tournament selection
{
    challonge_manager.displayTournaments(ui->tournamentListWidget);
    ui->challongeBackButton->setEnabled(false);
    tournamentsMode = true;
    ui->matchGroupBox->setEnabled(false);
    ui->completedMatchesButton->setEnabled(false);
    ui->reopenMatchButton->setEnabled(false);
}

void elscontroller::on_challongeRefreshButton_clicked()
{
    if (tournamentsMode)
        challonge_manager.displayTournaments(ui->tournamentListWidget);
    else
        challonge_manager.displayMatches(currentTourneyID, ui->tournamentListWidget, matchesShown);
    ui->matchGroupBox->setEnabled(false); // do not allow any more editing of the current match regardless of the mode
}

void elscontroller::on_challongeSubmitButton_clicked()
{
    QString score = QString::number(ui->challongeP1SpinBox->value()) + "-" +
                        QString::number(ui->challongeP2SpinBox->value());
    QString winner;
    if (ui->p1WinnerCheckBox->isChecked())
    {
        winner = currentMatch->getP1ID();
    }
    else if (ui->p2WinnerCheckBox->isChecked())
    {
        winner = currentMatch->getP2ID();
    }
    challonge_manager.updateMatch(currentMatch->getTourneyID(), currentMatch->getmatchID(), score, winner);
    if (!winner.isEmpty())
    {
        delete ui->tournamentListWidget->takeItem(ui->tournamentListWidget->currentRow());
        currentMatch = nullptr;
        ui->challongeSubmitButton->setEnabled(false);
        ui->challongeSubmitUpdateButton->setEnabled(false);
    }
}

void elscontroller::on_updateScoreboardButton_clicked()
{
    QString p1 = ui->matchP1Label->text();
    QString p2 = ui->matchP2Label->text();
    int p1_score = ui->challongeP1SpinBox->value();
    int p2_score = ui->challongeP2SpinBox->value();

    ui->p1LineEdit->setText(p1);
    ui->p2LineEdit->setText(p2);
    ui->p1SpinBox->setValue(p1_score);
    ui->p2SpinBox->setValue(p2_score);
    on_updateButton_clicked();
}

void elscontroller::on_challongeSubmitUpdateButton_clicked()
{
    on_challongeSubmitButton_clicked();
    on_updateScoreboardButton_clicked();
}

void elscontroller::on_p1WinnerCheckBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked)
        ui->p2WinnerCheckBox->setEnabled(true);
    else if (arg1 == Qt::Checked)   // dunno if Qt::PartiallyChecked will ever appear but will just account for it in case
    {
        ui->p2WinnerCheckBox->setEnabled(false);
    }
}

void elscontroller::on_p2WinnerCheckBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked)
        ui->p1WinnerCheckBox->setEnabled(true);
    else if (arg1 == Qt::Checked)   // dunno if Qt::PartiallyChecked will ever appear but will just account for it in case
        ui->p1WinnerCheckBox->setEnabled(false);
}

void elscontroller::on_swapSidesButton_clicked()
{
    QString p1_temp = ui->p1LineEdit->text();
    int p1_score_temp = ui->p1SpinBox->value();
    ui->p1LineEdit->setText(ui->p2LineEdit->text());
    ui->p1SpinBox->setValue(ui->p2SpinBox->value());
    ui->p2LineEdit->setText(p1_temp);
    ui->p2SpinBox->setValue(p1_score_temp);
}

void elscontroller::on_p1CopyNameButton_clicked()
{
    copyTextToClipBoard(ui->matchP1Label->text());
}

void elscontroller::on_p2CopyNameButton_clicked()
{
    copyTextToClipBoard(ui->matchP2Label->text());
}

void elscontroller::on_completedMatchesButton_clicked()
{
    if (ui->completedMatchesButton->text() == QString("View Done"))
    {
        challonge_manager.displayMatches(currentTourneyID, ui->tournamentListWidget, true); // show completed matches
        ui->completedMatchesButton->setText("View Not Done");
        matchesShown = true;
        ui->reopenMatchButton->setEnabled(true);
        ui->matchGroupBox->setEnabled(false);
    }
    else
    {
        challonge_manager.displayMatches(currentTourneyID, ui->tournamentListWidget, false); // show in-progress matches
        ui->completedMatchesButton->setText("View Done");
        matchesShown = false;
        ui->reopenMatchButton->setEnabled(false);
    }
}

void elscontroller::on_reopenMatchButton_clicked()
{
    if (ui->tournamentListWidget->currentItem() == nullptr)
    {
        setConsoleText("Nothing selected!");
        return;
    }
    MatchListWidgetItem* selectedMatch = static_cast<MatchListWidgetItem*>(ui->tournamentListWidget->currentItem());    // cast from ListWidgetItem*
    challonge_manager.reopenMatch(selectedMatch->getTourneyID(), selectedMatch->getmatchID());
    delete ui->tournamentListWidget->takeItem(ui->tournamentListWidget->currentRow());
}
/*
void elscontroller::on_copyButtonMsg1_clicked()
{
    copyTextToClipBoard(ui->copyEdit1->text());
}

void elscontroller::on_copyButtonMsg2_clicked()
{
    copyTextToClipBoard(ui->copyEdit2->text());
}

void elscontroller::on_copyButtonMsg3_clicked()
{
    copyTextToClipBoard(ui->copyEdit3->text());
}
*/

void elscontroller::on_twitchConnectButton_clicked()
{
    QString url = twitch_manager.getTwitchConnectURL();
    QDesktopServices::openUrl(QUrl(url));
}

void elscontroller::on_twitchValidateButton_clicked()
{
    QString redirect_url = ui->redirectURILineEdit->text();
    if (redirect_url.isEmpty())
    {
        setConsoleText("Twitch redirect URL cannot be empty!", 10);
        return;
    }
    twitch_manager.validateRedirectURL(redirect_url);
}

void elscontroller::on_twitchRefreshButton_clicked()
{
    twitch_manager.getStreamInfo();
}

void elscontroller::on_twitchSignOutButton_clicked()
{
    ui->redirectURILineEdit->clear();
    twitch_manager.signOut();
}

void elscontroller::timer_done()
{
    QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(timer_done()));
    ui->twitchClipStreamButton->setEnabled(true);
}

void elscontroller::on_twitchClipStreamButton_clicked()
{
    twitch_manager.clipStream();
    ui->twitchClipStreamButton->setEnabled(false);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timer_done()));
    timer->start(5000); // 5 seconds
}
