/********************************************************************************
** Form generated from reading UI file 'elscontroller.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELSCONTROLLER_H
#define UI_ELSCONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_elscontroller
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *info1LineEdit;
    QWidget *scoreboardTab;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBoxRight;
    QGridLayout *gridLayout;
    QListWidget *mapListWidget;
    QPushButton *pickMapButton;
    QLabel *mapResultLabel;
    QGroupBox *groupBoxLeft;
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *p1SpinBox;
    QLineEdit *p1LineEdit;
    QLabel *label;
    QLineEdit *p2LineEdit;
    QSpinBox *p2SpinBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *swapSidesButton;
    QLabel *infoLabel;
    QLineEdit *file1LineEdit;
    QLabel *infoLabel_2;
    QLineEdit *file2LineEdit;
    QLabel *infoLabel_3;
    QLineEdit *file3LineEdit;
    QPushButton *updateButton;
    QWidget *challongeTab;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QGroupBox *tournamentsGroupBox;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *challongeDescriptionLabel;
    QLineEdit *apiLineEdit;
    QPushButton *challongeSignInButton;
    QListWidget *tournamentListWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *challongeBackButton;
    QPushButton *challongeSelectButton;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *challongeRefreshButton;
    QPushButton *challongeSignOutButton;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *reopenMatchButton;
    QPushButton *completedMatchesButton;
    QGroupBox *matchGroupBox;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_3;
    QGroupBox *playerGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *matchP1Label;
    QLabel *matchVSLabel;
    QLabel *matchP2Label;
    QLabel *roundLabel;
    QPushButton *p1CopyNameButton;
    QPushButton *p2CopyNameButton;
    QGroupBox *matchInfoGroupBox;
    QGridLayout *gridLayout_4;
    QLabel *matchHyphenLabel;
    QCheckBox *p1WinnerCheckBox;
    QCheckBox *p2WinnerCheckBox;
    QPushButton *updateScoreboardButton;
    QSpinBox *challongeP2SpinBox;
    QSpinBox *challongeP1SpinBox;
    QPushButton *challongeSubmitUpdateButton;
    QPushButton *challongeSubmitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *elscontroller)
    {
        if (elscontroller->objectName().isEmpty())
            elscontroller->setObjectName(QStringLiteral("elscontroller"));
        elscontroller->resize(750, 500);
        elscontroller->setMinimumSize(QSize(750, 500));
        elscontroller->setAcceptDrops(false);
        centralwidget = new QWidget(elscontroller);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        info1LineEdit = new QTabWidget(centralwidget);
        info1LineEdit->setObjectName(QStringLiteral("info1LineEdit"));
        info1LineEdit->setMinimumSize(QSize(0, 0));
        scoreboardTab = new QWidget();
        scoreboardTab->setObjectName(QStringLiteral("scoreboardTab"));
        gridLayout_2 = new QGridLayout(scoreboardTab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBoxRight = new QGroupBox(scoreboardTab);
        groupBoxRight->setObjectName(QStringLiteral("groupBoxRight"));
        gridLayout = new QGridLayout(groupBoxRight);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mapListWidget = new QListWidget(groupBoxRight);
        mapListWidget->setObjectName(QStringLiteral("mapListWidget"));

        gridLayout->addWidget(mapListWidget, 0, 0, 1, 1);

        pickMapButton = new QPushButton(groupBoxRight);
        pickMapButton->setObjectName(QStringLiteral("pickMapButton"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        pickMapButton->setFont(font);

        gridLayout->addWidget(pickMapButton, 1, 0, 1, 1);

        mapResultLabel = new QLabel(groupBoxRight);
        mapResultLabel->setObjectName(QStringLiteral("mapResultLabel"));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        mapResultLabel->setFont(font1);
        mapResultLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(mapResultLabel, 2, 0, 1, 1);


        gridLayout_2->addWidget(groupBoxRight, 0, 1, 1, 1);

        groupBoxLeft = new QGroupBox(scoreboardTab);
        groupBoxLeft->setObjectName(QStringLiteral("groupBoxLeft"));
        horizontalLayout_4 = new QHBoxLayout(groupBoxLeft);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        splitter_2 = new QSplitter(groupBoxLeft);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter_2->setChildrenCollapsible(false);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        p1SpinBox = new QSpinBox(layoutWidget);
        p1SpinBox->setObjectName(QStringLiteral("p1SpinBox"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        p1SpinBox->setFont(font2);
        p1SpinBox->setStyleSheet(QStringLiteral("selection-color:black;selection-background-color:white"));
        p1SpinBox->setMinimum(-99);

        horizontalLayout_2->addWidget(p1SpinBox);

        p1LineEdit = new QLineEdit(layoutWidget);
        p1LineEdit->setObjectName(QStringLiteral("p1LineEdit"));
        p1LineEdit->setFont(font2);
        p1LineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(p1LineEdit);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        p2LineEdit = new QLineEdit(layoutWidget);
        p2LineEdit->setObjectName(QStringLiteral("p2LineEdit"));
        p2LineEdit->setFont(font2);
        p2LineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(p2LineEdit);

        p2SpinBox = new QSpinBox(layoutWidget);
        p2SpinBox->setObjectName(QStringLiteral("p2SpinBox"));
        p2SpinBox->setFont(font2);
        p2SpinBox->setStyleSheet(QStringLiteral("selection-color:black;selection-background-color:white"));
        p2SpinBox->setMinimum(-99);

        horizontalLayout_2->addWidget(p2SpinBox);

        splitter_2->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        swapSidesButton = new QPushButton(layoutWidget1);
        swapSidesButton->setObjectName(QStringLiteral("swapSidesButton"));

        verticalLayout->addWidget(swapSidesButton);

        infoLabel = new QLabel(layoutWidget1);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        QFont font4;
        font4.setBold(true);
        font4.setWeight(75);
        infoLabel->setFont(font4);
        infoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(infoLabel);

        file1LineEdit = new QLineEdit(layoutWidget1);
        file1LineEdit->setObjectName(QStringLiteral("file1LineEdit"));
        file1LineEdit->setFont(font);

        verticalLayout->addWidget(file1LineEdit);

        infoLabel_2 = new QLabel(layoutWidget1);
        infoLabel_2->setObjectName(QStringLiteral("infoLabel_2"));
        infoLabel_2->setFont(font4);
        infoLabel_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(infoLabel_2);

        file2LineEdit = new QLineEdit(layoutWidget1);
        file2LineEdit->setObjectName(QStringLiteral("file2LineEdit"));
        file2LineEdit->setFont(font);

        verticalLayout->addWidget(file2LineEdit);

        infoLabel_3 = new QLabel(layoutWidget1);
        infoLabel_3->setObjectName(QStringLiteral("infoLabel_3"));
        infoLabel_3->setFont(font4);
        infoLabel_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(infoLabel_3);

        file3LineEdit = new QLineEdit(layoutWidget1);
        file3LineEdit->setObjectName(QStringLiteral("file3LineEdit"));
        file3LineEdit->setFont(font);

        verticalLayout->addWidget(file3LineEdit);

        updateButton = new QPushButton(layoutWidget1);
        updateButton->setObjectName(QStringLiteral("updateButton"));
        updateButton->setFont(font);

        verticalLayout->addWidget(updateButton);

        splitter_2->addWidget(layoutWidget1);

        horizontalLayout_4->addWidget(splitter_2);


        gridLayout_2->addWidget(groupBoxLeft, 0, 0, 1, 1);

        info1LineEdit->addTab(scoreboardTab, QString());
        challongeTab = new QWidget();
        challongeTab->setObjectName(QStringLiteral("challongeTab"));
        horizontalLayout_3 = new QHBoxLayout(challongeTab);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        splitter = new QSplitter(challongeTab);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);
        tournamentsGroupBox = new QGroupBox(splitter);
        tournamentsGroupBox->setObjectName(QStringLiteral("tournamentsGroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tournamentsGroupBox->sizePolicy().hasHeightForWidth());
        tournamentsGroupBox->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(tournamentsGroupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        challongeDescriptionLabel = new QLabel(tournamentsGroupBox);
        challongeDescriptionLabel->setObjectName(QStringLiteral("challongeDescriptionLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, challongeDescriptionLabel);

        apiLineEdit = new QLineEdit(tournamentsGroupBox);
        apiLineEdit->setObjectName(QStringLiteral("apiLineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(apiLineEdit->sizePolicy().hasHeightForWidth());
        apiLineEdit->setSizePolicy(sizePolicy2);
        apiLineEdit->setMaxLength(100);
        apiLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::SpanningRole, apiLineEdit);

        challongeSignInButton = new QPushButton(tournamentsGroupBox);
        challongeSignInButton->setObjectName(QStringLiteral("challongeSignInButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(challongeSignInButton->sizePolicy().hasHeightForWidth());
        challongeSignInButton->setSizePolicy(sizePolicy3);

        formLayout->setWidget(2, QFormLayout::SpanningRole, challongeSignInButton);


        verticalLayout_2->addLayout(formLayout);

        tournamentListWidget = new QListWidget(tournamentsGroupBox);
        tournamentListWidget->setObjectName(QStringLiteral("tournamentListWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tournamentListWidget->sizePolicy().hasHeightForWidth());
        tournamentListWidget->setSizePolicy(sizePolicy4);
        tournamentListWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tournamentListWidget->setResizeMode(QListView::Adjust);

        verticalLayout_2->addWidget(tournamentListWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        challongeBackButton = new QPushButton(tournamentsGroupBox);
        challongeBackButton->setObjectName(QStringLiteral("challongeBackButton"));

        horizontalLayout_5->addWidget(challongeBackButton);

        challongeSelectButton = new QPushButton(tournamentsGroupBox);
        challongeSelectButton->setObjectName(QStringLiteral("challongeSelectButton"));

        horizontalLayout_5->addWidget(challongeSelectButton);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        challongeRefreshButton = new QPushButton(tournamentsGroupBox);
        challongeRefreshButton->setObjectName(QStringLiteral("challongeRefreshButton"));

        horizontalLayout_6->addWidget(challongeRefreshButton);

        challongeSignOutButton = new QPushButton(tournamentsGroupBox);
        challongeSignOutButton->setObjectName(QStringLiteral("challongeSignOutButton"));

        horizontalLayout_6->addWidget(challongeSignOutButton);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        reopenMatchButton = new QPushButton(tournamentsGroupBox);
        reopenMatchButton->setObjectName(QStringLiteral("reopenMatchButton"));
        reopenMatchButton->setEnabled(false);

        horizontalLayout_7->addWidget(reopenMatchButton);

        completedMatchesButton = new QPushButton(tournamentsGroupBox);
        completedMatchesButton->setObjectName(QStringLiteral("completedMatchesButton"));
        completedMatchesButton->setEnabled(false);

        horizontalLayout_7->addWidget(completedMatchesButton);


        verticalLayout_2->addLayout(horizontalLayout_7);

        splitter->addWidget(tournamentsGroupBox);
        matchGroupBox = new QGroupBox(splitter);
        matchGroupBox->setObjectName(QStringLiteral("matchGroupBox"));
        matchGroupBox->setEnabled(true);
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(2);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(matchGroupBox->sizePolicy().hasHeightForWidth());
        matchGroupBox->setSizePolicy(sizePolicy5);
        verticalLayout_3 = new QVBoxLayout(matchGroupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        splitter_3 = new QSplitter(matchGroupBox);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter_3->setChildrenCollapsible(false);
        playerGroupBox = new QGroupBox(splitter_3);
        playerGroupBox->setObjectName(QStringLiteral("playerGroupBox"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(1);
        sizePolicy6.setHeightForWidth(playerGroupBox->sizePolicy().hasHeightForWidth());
        playerGroupBox->setSizePolicy(sizePolicy6);
        gridLayout_3 = new QGridLayout(playerGroupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        matchP1Label = new QLabel(playerGroupBox);
        matchP1Label->setObjectName(QStringLiteral("matchP1Label"));
        sizePolicy.setHeightForWidth(matchP1Label->sizePolicy().hasHeightForWidth());
        matchP1Label->setSizePolicy(sizePolicy);
        QFont font5;
        font5.setPointSize(13);
        font5.setBold(true);
        font5.setWeight(75);
        matchP1Label->setFont(font5);
        matchP1Label->setAutoFillBackground(true);
        matchP1Label->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(matchP1Label, 0, 0, 1, 1);

        matchVSLabel = new QLabel(playerGroupBox);
        matchVSLabel->setObjectName(QStringLiteral("matchVSLabel"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(3);
        sizePolicy7.setHeightForWidth(matchVSLabel->sizePolicy().hasHeightForWidth());
        matchVSLabel->setSizePolicy(sizePolicy7);
        matchVSLabel->setFont(font5);
        matchVSLabel->setAutoFillBackground(true);
        matchVSLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(matchVSLabel, 0, 1, 1, 1);

        matchP2Label = new QLabel(playerGroupBox);
        matchP2Label->setObjectName(QStringLiteral("matchP2Label"));
        sizePolicy.setHeightForWidth(matchP2Label->sizePolicy().hasHeightForWidth());
        matchP2Label->setSizePolicy(sizePolicy);
        matchP2Label->setFont(font5);
        matchP2Label->setAutoFillBackground(true);
        matchP2Label->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(matchP2Label, 0, 2, 1, 1);

        roundLabel = new QLabel(playerGroupBox);
        roundLabel->setObjectName(QStringLiteral("roundLabel"));
        sizePolicy6.setHeightForWidth(roundLabel->sizePolicy().hasHeightForWidth());
        roundLabel->setSizePolicy(sizePolicy6);
        QFont font6;
        font6.setPointSize(11);
        roundLabel->setFont(font6);
        roundLabel->setAutoFillBackground(true);
        roundLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(roundLabel, 1, 1, 1, 1);

        p1CopyNameButton = new QPushButton(playerGroupBox);
        p1CopyNameButton->setObjectName(QStringLiteral("p1CopyNameButton"));

        gridLayout_3->addWidget(p1CopyNameButton, 1, 0, 1, 1);

        p2CopyNameButton = new QPushButton(playerGroupBox);
        p2CopyNameButton->setObjectName(QStringLiteral("p2CopyNameButton"));

        gridLayout_3->addWidget(p2CopyNameButton, 1, 2, 1, 1);

        splitter_3->addWidget(playerGroupBox);
        matchInfoGroupBox = new QGroupBox(splitter_3);
        matchInfoGroupBox->setObjectName(QStringLiteral("matchInfoGroupBox"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(2);
        sizePolicy8.setHeightForWidth(matchInfoGroupBox->sizePolicy().hasHeightForWidth());
        matchInfoGroupBox->setSizePolicy(sizePolicy8);
        gridLayout_4 = new QGridLayout(matchInfoGroupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        matchHyphenLabel = new QLabel(matchInfoGroupBox);
        matchHyphenLabel->setObjectName(QStringLiteral("matchHyphenLabel"));
        sizePolicy7.setHeightForWidth(matchHyphenLabel->sizePolicy().hasHeightForWidth());
        matchHyphenLabel->setSizePolicy(sizePolicy7);
        QFont font7;
        font7.setPointSize(18);
        font7.setBold(true);
        font7.setWeight(75);
        matchHyphenLabel->setFont(font7);
        matchHyphenLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(matchHyphenLabel, 0, 1, 1, 1);

        p1WinnerCheckBox = new QCheckBox(matchInfoGroupBox);
        p1WinnerCheckBox->setObjectName(QStringLiteral("p1WinnerCheckBox"));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(1);
        sizePolicy9.setHeightForWidth(p1WinnerCheckBox->sizePolicy().hasHeightForWidth());
        p1WinnerCheckBox->setSizePolicy(sizePolicy9);

        gridLayout_4->addWidget(p1WinnerCheckBox, 1, 0, 1, 1);

        p2WinnerCheckBox = new QCheckBox(matchInfoGroupBox);
        p2WinnerCheckBox->setObjectName(QStringLiteral("p2WinnerCheckBox"));
        sizePolicy9.setHeightForWidth(p2WinnerCheckBox->sizePolicy().hasHeightForWidth());
        p2WinnerCheckBox->setSizePolicy(sizePolicy9);

        gridLayout_4->addWidget(p2WinnerCheckBox, 1, 2, 1, 1);

        updateScoreboardButton = new QPushButton(matchInfoGroupBox);
        updateScoreboardButton->setObjectName(QStringLiteral("updateScoreboardButton"));
        sizePolicy9.setHeightForWidth(updateScoreboardButton->sizePolicy().hasHeightForWidth());
        updateScoreboardButton->setSizePolicy(sizePolicy9);

        gridLayout_4->addWidget(updateScoreboardButton, 2, 1, 1, 1);

        challongeP2SpinBox = new QSpinBox(matchInfoGroupBox);
        challongeP2SpinBox->setObjectName(QStringLiteral("challongeP2SpinBox"));
        QSizePolicy sizePolicy10(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(3);
        sizePolicy10.setHeightForWidth(challongeP2SpinBox->sizePolicy().hasHeightForWidth());
        challongeP2SpinBox->setSizePolicy(sizePolicy10);
        challongeP2SpinBox->setFont(font7);
        challongeP2SpinBox->setStyleSheet(QStringLiteral("selection-color:black;selection-background-color:white"));
        challongeP2SpinBox->setAlignment(Qt::AlignCenter);
        challongeP2SpinBox->setMinimum(-99);

        gridLayout_4->addWidget(challongeP2SpinBox, 0, 2, 1, 1);

        challongeP1SpinBox = new QSpinBox(matchInfoGroupBox);
        challongeP1SpinBox->setObjectName(QStringLiteral("challongeP1SpinBox"));
        QSizePolicy sizePolicy11(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(2);
        sizePolicy11.setHeightForWidth(challongeP1SpinBox->sizePolicy().hasHeightForWidth());
        challongeP1SpinBox->setSizePolicy(sizePolicy11);
        challongeP1SpinBox->setFont(font7);
        challongeP1SpinBox->setStyleSheet(QStringLiteral("selection-color:black;selection-background-color:white"));
        challongeP1SpinBox->setAlignment(Qt::AlignCenter);
        challongeP1SpinBox->setMinimum(-99);

        gridLayout_4->addWidget(challongeP1SpinBox, 0, 0, 1, 1);

        challongeSubmitUpdateButton = new QPushButton(matchInfoGroupBox);
        challongeSubmitUpdateButton->setObjectName(QStringLiteral("challongeSubmitUpdateButton"));
        sizePolicy9.setHeightForWidth(challongeSubmitUpdateButton->sizePolicy().hasHeightForWidth());
        challongeSubmitUpdateButton->setSizePolicy(sizePolicy9);

        gridLayout_4->addWidget(challongeSubmitUpdateButton, 2, 2, 1, 1);

        challongeSubmitButton = new QPushButton(matchInfoGroupBox);
        challongeSubmitButton->setObjectName(QStringLiteral("challongeSubmitButton"));
        sizePolicy9.setHeightForWidth(challongeSubmitButton->sizePolicy().hasHeightForWidth());
        challongeSubmitButton->setSizePolicy(sizePolicy9);

        gridLayout_4->addWidget(challongeSubmitButton, 2, 0, 1, 1);

        splitter_3->addWidget(matchInfoGroupBox);

        verticalLayout_3->addWidget(splitter_3);

        splitter->addWidget(matchGroupBox);

        horizontalLayout_3->addWidget(splitter);

        info1LineEdit->addTab(challongeTab, QString());

        horizontalLayout->addWidget(info1LineEdit);

        elscontroller->setCentralWidget(centralwidget);
        menubar = new QMenuBar(elscontroller);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 20));
        elscontroller->setMenuBar(menubar);
        statusbar = new QStatusBar(elscontroller);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        elscontroller->setStatusBar(statusbar);

        retranslateUi(elscontroller);

        info1LineEdit->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(elscontroller);
    } // setupUi

    void retranslateUi(QMainWindow *elscontroller)
    {
        elscontroller->setWindowTitle(QApplication::translate("elscontroller", "Elsword Tournament Controller", nullptr));
        groupBoxRight->setTitle(QApplication::translate("elscontroller", "Random Map", nullptr));
        pickMapButton->setText(QApplication::translate("elscontroller", "Pick Random Map", nullptr));
        mapResultLabel->setText(QApplication::translate("elscontroller", "Result", nullptr));
        groupBoxLeft->setTitle(QApplication::translate("elscontroller", "Display Files", nullptr));
        p1LineEdit->setPlaceholderText(QApplication::translate("elscontroller", "Player1", nullptr));
        label->setText(QApplication::translate("elscontroller", "VS.", nullptr));
        p2LineEdit->setPlaceholderText(QApplication::translate("elscontroller", "Player2", nullptr));
        swapSidesButton->setText(QApplication::translate("elscontroller", "Swap Sides", nullptr));
        infoLabel->setText(QApplication::translate("elscontroller", "Info - 1 (Tournament Name, Round Info, brackets, etc)", nullptr));
        infoLabel_2->setText(QApplication::translate("elscontroller", "Info - 2 (Tournament Name, Round Info, brackets, etc)", nullptr));
        infoLabel_3->setText(QApplication::translate("elscontroller", "Info - 3 (Tournament Name, Round Info, brackets, etc)", nullptr));
        updateButton->setText(QApplication::translate("elscontroller", "Update", nullptr));
        info1LineEdit->setTabText(info1LineEdit->indexOf(scoreboardTab), QApplication::translate("elscontroller", "Scoreboard HUD", nullptr));
        tournamentsGroupBox->setTitle(QApplication::translate("elscontroller", "Tournament/Match Selection", nullptr));
        challongeDescriptionLabel->setText(QApplication::translate("elscontroller", "Challonge API Key:", nullptr));
        challongeSignInButton->setText(QApplication::translate("elscontroller", "Sign In", nullptr));
        challongeBackButton->setText(QApplication::translate("elscontroller", "Back", nullptr));
        challongeSelectButton->setText(QApplication::translate("elscontroller", "Select", nullptr));
        challongeRefreshButton->setText(QApplication::translate("elscontroller", "Refresh", nullptr));
        challongeSignOutButton->setText(QApplication::translate("elscontroller", "Sign Out", nullptr));
        reopenMatchButton->setText(QApplication::translate("elscontroller", "Re-Open", nullptr));
        completedMatchesButton->setText(QApplication::translate("elscontroller", "View Done", nullptr));
        matchGroupBox->setTitle(QApplication::translate("elscontroller", "Match Info", nullptr));
        playerGroupBox->setTitle(QString());
        matchP1Label->setText(QApplication::translate("elscontroller", "Player1", nullptr));
        matchVSLabel->setText(QApplication::translate("elscontroller", "VS.", nullptr));
        matchP2Label->setText(QApplication::translate("elscontroller", "Player2", nullptr));
#ifndef QT_NO_STATUSTIP
        roundLabel->setStatusTip(QApplication::translate("elscontroller", "Link to brackets (opens in default browser).", nullptr));
#endif // QT_NO_STATUSTIP
        roundLabel->setText(QApplication::translate("elscontroller", "Round 1", nullptr));
        p1CopyNameButton->setText(QApplication::translate("elscontroller", "Copy to Clipboard", nullptr));
        p2CopyNameButton->setText(QApplication::translate("elscontroller", "Copy to Clipboard", nullptr));
        matchInfoGroupBox->setTitle(QApplication::translate("elscontroller", "Report Scores", nullptr));
        matchHyphenLabel->setText(QApplication::translate("elscontroller", "\342\200\224", nullptr));
        p1WinnerCheckBox->setText(QApplication::translate("elscontroller", " Winner", nullptr));
        p2WinnerCheckBox->setText(QApplication::translate("elscontroller", " Winner", nullptr));
        updateScoreboardButton->setText(QApplication::translate("elscontroller", "Update Scoreboard", nullptr));
        challongeSubmitUpdateButton->setText(QApplication::translate("elscontroller", "Submit and Update", nullptr));
        challongeSubmitButton->setText(QApplication::translate("elscontroller", "Submit to Challonge", nullptr));
        info1LineEdit->setTabText(info1LineEdit->indexOf(challongeTab), QApplication::translate("elscontroller", "Challonge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class elscontroller: public Ui_elscontroller {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELSCONTROLLER_H
