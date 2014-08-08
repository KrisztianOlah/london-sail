#include "database.h"
#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QStandardPaths>

Database::Database() : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/data-1.0.sqlite";

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!dir.exists()) {
        dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    }
    db.setDatabaseName(path);
    open();
}
Database::~Database() {
    close();
}


//private:
void Database::close() { db.close(); }

bool Database::createStopsTable() {
    if (!isOpen()) { open();}
    if (isStopsTable()) { return true; }
    if (isOpen()) {
        QSqlQuery query;
        bool ret = query.exec("CREATE TABLE stopstable "
                              "(name STRING, "
                              "code STRING UNIQUE, "
                              "type INTEGER, "
                              "towards STRING, "
                              "latitude STRING, "
                              "longitude STRING, "
                              "stoppointindicator STRING, "
                              "favorite INTEGER)");
        if (!ret) {
            qDebug() << "query failed.";
            qDebug() << lastError();
        }
        return ret;
    }
    else {
        qDebug() << "database is closed";
        return false;
    }
}

bool Database::isOpen() const { return db.isOpen(); }

bool Database::isStopsTable() const {
    if (!isOpen()) { return false; }
    QSqlQuery query;
    bool ret = query.exec("SELECT * FROM stopstable");
    return ret;
}

bool Database::open() { return db.open(); }


//public:
bool Database::addStop(const QString& name,const QString& code,int type, QString& towards, double latitude, double longitude,
             const QString& stopPointIndicator, bool favorite) {
    if (createStopsTable()) {
        QSqlQuery query;
        query.prepare(
                      "INSERT OR IGNORE INTO stopstable (name, code, type, towards, latitude, longitude, stoppointindicator, favorite) "
                      "VALUES (:name, :code, :type, :towards, :latitude, :longitude, :stoppointindicator, :favorite)"
                      );
        query.bindValue(":name", name);
        query.bindValue(":code", code);
        query.bindValue(":type", type);
        query.bindValue(":towards", towards);
        query.bindValue(":latitude", latitude);
        query.bindValue(":longitude", longitude);
        query.bindValue(":stoppointindicator", stopPointIndicator);
        query.bindValue(":favorite", favorite);
        bool ret = query.exec();
        if (!ret) { qDebug() << "***Adding " << name << " failed ***"; }
        return ret;
    }
    else {
        qDebug() << "There is no db.";
        return false;
    }
}

bool Database::clearStopsTable() {
    QSqlQuery query;
    bool ok = query.exec("DELETE FROM stopstable WHERE favorite=0");
    return ok;
}

bool Database::isFavorite(const QString& code) const {
    QSqlQuery query;
    query.prepare("SELECT favorite FROM stopstable WHERE code= :code ");
    query.bindValue(":code", code);
    bool ok  = query.exec();
    bool ret = false;
    if (!ok) {
        qDebug() << "isFavorite() failed";
    }
    else {
        query.next();
        ret = query.value(0).toBool();
    }

    return ret;
}

QSqlError Database::lastError() const { return db.lastError(); }

bool Database::makeFavorite(const QString& code) {
    qDebug() << "makeFavorite() called";
    QSqlQuery query;
    query.prepare("UPDATE stopstable SET favorite=1 WHERE code= :code ");
    query.bindValue(":code", code);
    bool ret = query.exec();
    if (!ret) { qDebug() << "makeFavorite() failed."; }
    return ret;
}

bool Database::unFavorite(const QString& code) {
    qDebug() << "unFavorite() called";
    QSqlQuery query;
    query.prepare("UPDATE stopstable SET favorite=0 WHERE code= :code ");
    query.bindValue(":code", code);
    bool ret = query.exec();
    if (!ret) { qDebug() << "makeFavorite() failed."; }
    return ret;
}
