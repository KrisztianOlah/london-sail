/*
Copyright (C) 2014 Krisztian Olah

  email: fasza2mobile@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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

//creates stopstable and returns true if successful otherwise returns false
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

//returns true if stopstable is already present otherwise returns false
bool Database::isStopsTable() const {
    if (!isOpen()) { return false; }
    QSqlQuery query;
    bool ret = query.exec("SELECT * FROM stopstable");
    return ret;
}

bool Database::open() { return db.open(); }


//public:
//adds a new stop to stopstable and returns true if successful otherwise returns false
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

//deletes every entry in stopstable that is not set to favorite by user and returns true if successful otherwise returns fasle
bool Database::clearStopsTable() {
    QSqlQuery query;
    bool ok = query.exec("DELETE FROM stopstable WHERE favorite=0");
    return ok;
}

//checks if a given bus stop or pier(by their code) is favorite
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

//makes a stop a favorite, returns true on success and false otherwise
bool Database::makeFavorite(const QString& code) {
    qDebug() << "makeFavorite() called";
    QSqlQuery query;
    query.prepare("UPDATE stopstable SET favorite=1 WHERE code= :code ");
    query.bindValue(":code", code);
    bool ret = query.exec();
    if (!ret) { qDebug() << "makeFavorite() failed."; }
    return ret;
}

//makes a stop NOT favorite, returns true on success and false otherwise
bool Database::unFavorite(const QString& code) {
    qDebug() << "unFavorite() called";
    QSqlQuery query;
    query.prepare("UPDATE stopstable SET favorite=0 WHERE code= :code ");
    query.bindValue(":code", code);
    bool ret = query.exec();
    if (!ret) { qDebug() << "makeFavorite() failed."; }
    return ret;
}
