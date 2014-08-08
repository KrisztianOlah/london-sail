#include "databasemanager.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QVariant>


DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent)
{
}

//public:
bool DatabaseManager::addStop(const QString& name,const QString& code,int type, QString& towards, double latitude, double longitude,
             const QString& stopPointIndicator, bool favorite) {
    return db.addStop(name, code, type, towards, latitude, longitude, stopPointIndicator, favorite);
}

bool DatabaseManager::clearStopsTable() { return db.clearStopsTable(); }

bool DatabaseManager::isFavorite(const QString& code) { return db.isFavorite(code); }

bool DatabaseManager::makeFavorite(const QString& code) { return db.makeFavorite(code); }

bool DatabaseManager::unFavorite(const QString& code) { return db.unFavorite(code); }
