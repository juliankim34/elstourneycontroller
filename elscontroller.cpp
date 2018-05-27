#include "elscontroller.h"
#include "ui_elscontroller.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QtAlgorithms>

elscontroller::elscontroller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::elscontroller),
    challonge_manager(),
    currentMatch(nullptr)
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
}

elscontroller::~elscontroller()
{
    delete ui;
    if (currentMatch != nullptr)
        delete currentMatch;
    qDeleteAll(helpMenu->actions()); // guaranteed to have items due to constructor
    delete helpMenu;    // guaranteed to not be nullptr due to constructor
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
    QMessageBox::about(NULL, "About", "Elsword Tournament Controller by Synai\t\n\t  Made with Qt 5.10.1\t\n\t  License: LGPL\t");
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

void elscontroller::setMatch(QString p1, QString p2, QString round, QString score)
{
    QStringList scores;
    ui->matchP1Label->setText(p1);
    ui->matchP2Label->setText(p2);
    ui->roundLabel->setText(round);
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
        challonge_manager.displayMatches(currentTourneyID, ui->tournamentListWidget);
        tournamentsMode = false;
        ui->challongeBackButton->setEnabled(true);
    }
    else // update match info box
    {
        MatchListWidgetItem* selectedMatch = static_cast<MatchListWidgetItem*>(ui->tournamentListWidget->currentItem());    // cast from ListWidgetItem*
        currentMatch = selectedMatch;
        QString p1 = selectedMatch->getP1();
        QString p2 = selectedMatch->getP2();
        QString round = "Round " + selectedMatch->getRound();
        QString score = selectedMatch->getScore();
        setMatch(p1, p2, round, score);
        ui->matchGroupBox->setEnabled(true);
        ui->p1WinnerCheckBox->setChecked(false);
        ui->p2WinnerCheckBox->setChecked(false);
    }
}

void elscontroller::on_challongeSignOutButton_clicked()
{
    showChallongeUI(true, false, false);
    setConsoleText("Signed out.", 10);
}

void elscontroller::on_challongeBackButton_clicked() // this back button is only clickable to move from match selection -> tournament selection
{
    challonge_manager.displayTournaments(ui->tournamentListWidget);
    ui->challongeBackButton->setEnabled(false);
    tournamentsMode = true;
    ui->matchGroupBox->setEnabled(false);
}

void elscontroller::on_challongeRefreshButton_clicked()
{
    if (tournamentsMode)
        challonge_manager.displayTournaments(ui->tournamentListWidget);
    else
        challonge_manager.displayMatches(currentTourneyID, ui->tournamentListWidget);
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
        ui->matchGroupBox->setEnabled(false);
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

void elscontroller::on_pushButton_clicked()
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
