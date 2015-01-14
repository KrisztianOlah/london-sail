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

/// if (rankFrom = rankTo) {do nothing}
/// if (rankFrom > rankTo) { inrcement rank of all that are bigger than rankTo but smaller than rankFrom }
/// if (rankFrom < rankTo) { inrcement rank of all that are bigger than rankFrom but smaller than rankTo }
/// only add rank to favourites the rest will have none
/// when a new item is favorited it will get rank of the number of items that have a rank countRanked()
/// data is to be presented in descending order
Database::Database() : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/data-2.0.sqlite";

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!dir.exists()) {
        dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    }
    ////////TODO Check for old version of database and upgrade/alter it to the new one then rename it to match the new name
    db.setDatabaseName(path);
    open();
}

Database::~Database() {
    close();
}


//private:
void Database::close() { db.close(); }

//returns how many items in db has a rank, returns -1 if unsuccessful
int Database::countRanked() const {
    QSqlQuery query;
    query.setForwardOnly(true);
    bool ok = query.exec("SELECT * FROM stopstable WHERE rank IS NOT NULL");
    query.last();
    int count;
    if (query.at() < 0) { count = 0; }
    else { count = query.at() + 1; }
    if (ok) return count;
    else {
        qDebug() << lastError();
        return -1;
    }
}

//!!!!!!!!!!!!!!!!!!!!!!!NEED TO UPDATE OLD DB //ie copy data from old one or upgrade it somehow
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
                              "favorite INTEGER, "
                              "rank INTEGER)");
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

//returns the rank of a given item by code or returns ngative upon failiure
int Database::getRank(const QString& code) const {
    QSqlQuery query;
    query.prepare("SELECT rank FROM stopstable WHERE code = :code");
    query.bindValue(":code", code);
    query.exec();
    query.first();
    return query.value(0).toInt();
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

//makes a stop a favorite and ranks it as 1st, returns true on success and false otherwise
bool Database::makeFavorite(const QString& code) {
    QSqlQuery query, query_incr;
    //incrementing all ranks so that fresh results stay on the top for better usability
    bool isIncremented = query_incr.exec("UPDATE stopstable SET rank = rank + 1 ");
    query.prepare("UPDATE stopstable SET favorite=1, rank= 1 WHERE code= :code ");
    query.bindValue(":code", code);
    bool ret = query.exec();
    if (!ret || !isIncremented) { qDebug() << "makeFavorite() failed."; }
    return ret;
}

///TODO increment all ranks between the 2 that needs moving
bool Database::swapRanks(const QString& code1, const QString& code2) {
    ///getrank 1
    ///getrank 2
    /// set smaller to small, the other big, if equal return
    /// inrcement rank of all that are bigger than small but smaller than big
    QSqlQuery query;
    query.prepare("UPDATE stopstable SET rank = "
                            "(SELECT SUM(rank) FROM stopstable "
                            "WHERE code IN (code1, code2) ) - rank "
                  "WHERE code IN (code1, code2) "
                  "VALUES (?, ?, ?, ?)");
    query.bindValue(0,code1);
    query.bindValue(1,code2);
    query.bindValue(2,code1);
    query.bindValue(3,code2);
    bool ret = query.exec();
    if (!ret) qDebug() << "Swapping failed!";
    return ret;
}

//makes a stop NOT favorite and decrements the ranks of other items to eliminate gaps,
//returns true on success and false otherwise
bool Database::unFavorite(const QString& code) {
    qDebug() << "unFavorite() called on:" << code << "with rank:" << getRank(code);
    QSqlQuery query, query_dec;
    query_dec.prepare("UPDATE stopstable SET rank= rank - 1 WHERE rank > :current");
    query_dec.bindValue(":current", getRank(code));
    query.prepare("UPDATE stopstable SET favorite=0, rank=NULL WHERE code= :code ");
    query.bindValue(":code", code);
    bool isDecremented = query_dec.exec();
    bool isRemovedFromFavs = query.exec();
    if (!isRemovedFromFavs || !isDecremented) { qDebug() << "unFavorite() failed."; }
    return isRemovedFromFavs;
}
