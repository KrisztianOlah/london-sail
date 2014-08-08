#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>

class Database
{
public:
    Database();
public:
    ~Database();
private:
    QSqlDatabase db;
private:
    void close();
    bool createStopsTable();
    bool isOpen() const;
    bool isStopsTable() const;
    bool open();
public:
    bool addStop(const QString& name,const QString& code,int type, QString& towards,double latitude, double longitude,
                 const QString& stopPointIndicator = QString(), bool favorite = false);
    bool clearStopsTable();
    bool isFavorite(const QString& code) const;
    QSqlError lastError() const;
    bool makeFavorite(const QString& code);
    bool unFavorite(const QString& code);
};

#endif // DATABASE_H
