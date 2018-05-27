#include "mapmanager.h"
#include <QTextStream>
#include <QListWidgetItem>
#include <vector>
#include <cstdlib>
#include <ctime>

MapManager::MapManager()
{
}

void MapManager::setupFile()
{
    maplist.setFileName(":/maplist.txt");
}

void MapManager::addMapsToListWidget(QListWidget *list)
{
    maplist.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&maplist);

    while (!in.atEnd())
    {
        QString map = in.readLine();
        QListWidgetItem* toAdd = constructWidgetItem(map);
        list->addItem(toAdd);
    }
    maplist.close();
}

QListWidgetItem* MapManager::constructWidgetItem(QString map)
{
    QListWidgetItem* item = new QListWidgetItem(map);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    return item;
}

QString MapManager::pickRandomMap(QListWidget *list)
{
    int row;
    std::vector<QString> selected;
    for (row = 0; row < list->count(); row++)
    {
        if (list->item(row)->checkState() == Qt::Checked)
        {
            selected.push_back(list->item(row)->text());
        }
    }
    if (selected.size() == 0)
    {
        return QString("No map(s) selected!");
    }
    //std::srand(std::time(nullptr)); // use current time as seed
    int randMap = rand() % selected.size();
    return selected[randMap];
}

void MapManager::clearMapSelections(QListWidget *list)
{
    for (int row = 0; row < list->count(); row++)
    {
        list->item(row)->setCheckState(Qt::Unchecked);
    }
}

void MapManager::selectAllMaps(QListWidget *list)
{
    for (int row = 0; row < list->count(); row++)
    {
        list->item(row)->setCheckState(Qt::Checked);
    }
}
