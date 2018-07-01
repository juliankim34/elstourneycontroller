#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>

class FileManager;

class FileManager
{
private:
    QFile player1NameFile;
    QFile player2NameFile;
    QFile player1ScoreFile;
    QFile player2ScoreFile;
    QFile infoFile1;
    QFile infoFile2;
    QFile infoFile3;
    QFile xmlFile;

    void openFiles();
    void closeFiles();
    int writeFile(QFile &file, QString text);
    int writeXMLFile(QFile &xmlFile, QString p1_name, QString p2_name, QString p1_score, QString p2_score);

public:
    FileManager();
    int writeGameInfo(QString p1_name, QString p2_name, QString p1_score, QString p2_score, QString info_1, QString info_2, QString info_3);
    void setupFiles();
    FileManager& operator=(const FileManager& other) = default;
};

#endif // FILEMANAGER_H
