#include "filemanager.h"
#include <QDir>

FileManager::FileManager()
{
    //setupFiles();
}

int FileManager::writeGameInfo(QString p1_name, QString p2_name,
                               QString p1_score, QString p2_score,
                               QString info_1, QString info_2, QString info_3)
{
    int ret = 0;
    openFiles();

    ret += writeFile(player1NameFile, p1_name);
    ret += writeFile(player2NameFile, p2_name);
    ret += writeFile(player1ScoreFile, p1_score);
    ret += writeFile(player2ScoreFile, p2_score);
    ret += writeFile(infoFile1, info_1);
    ret += writeFile(infoFile2, info_2);
    ret += writeFile(infoFile3, info_3);

    closeFiles();

    return ret;
}

void FileManager::setupFiles()
{
    QDir dir;
    if (!dir.exists("info"))
        dir.mkdir("info");
    player1NameFile.setFileName("info/player1_name.txt");
    player2NameFile.setFileName("info/player2_name.txt");
    player1ScoreFile.setFileName("info/player1_score.txt");
    player2ScoreFile.setFileName("info/player2_score.txt");
    infoFile1.setFileName("info/info_1.txt");
    infoFile2.setFileName("info/info_2.txt");
    infoFile3.setFileName("info/info_3.txt");
}

void FileManager::openFiles()
{
    player1NameFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    player2NameFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    player1ScoreFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    player2ScoreFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    infoFile1.open(QIODevice::WriteOnly | QIODevice::Truncate);
    infoFile2.open(QIODevice::WriteOnly | QIODevice::Truncate);
    infoFile3.open(QIODevice::WriteOnly | QIODevice::Truncate);
}

void FileManager::closeFiles()  // closing an unopened file results in nothing for a QFile, no error checking needed
{
    player1NameFile.close();
    player2NameFile.close();
    player1ScoreFile.close();
    player2ScoreFile.close();
    infoFile1.close();
    infoFile2.close();
    infoFile3.close();
}

int FileManager::writeFile(QFile &file, QString text)
{
    if (!file.exists())
    {
        return 1; // error
    }

    QTextStream stream(&file);
    stream << text;

    //file.resize(file.pos());
    return 0;
}
