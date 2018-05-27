#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QListWidget>

class MapManager;

class MapManager
{
private:
    QFile maplist;
    QListWidgetItem* constructWidgetItem(QString map);

public:
    MapManager();
    void setupFile();
    void addMapsToListWidget(QListWidget* list);
    QString pickRandomMap(QListWidget* list);
    void clearMapSelections(QListWidget* list);
    void selectAllMaps(QListWidget* list);
};

#endif // MAPMANAGER_H
