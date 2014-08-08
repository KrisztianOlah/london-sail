#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "database.h"

class QSqlDatabase;

class DatabaseManager : public QObject
{
public:
    explicit DatabaseManager(QObject* parent = 0);
private:
    Database db;
public:
    bool addStop(const QString& name,const QString& code,int type, QString& towards,double latitude, double longitude,
                 const QString& stopPointIndicator = QString(), bool favorite = false);
    bool clearStopsTable();
    bool isFavorite(const QString& code);
    bool makeFavorite(const QString& code);
    bool unFavorite(const QString& code);
};

#endif // DATABASEMANAGER_H
