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
#include <QFile>
#include <QSqlQuery>
#include <QStandardPaths>


Database::Database() : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/data-2.0.sqlite";

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!dir.exists()) {
        dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    }
    if (upgrade()) {
        db.setDatabaseName(path);
        bool ok = open();
        if (!ok) qDebug() << "Couldn't open db.";
    }
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

//returns the rank of a given item by code or returns negative upon failure
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

bool Database::upgrade() {
    QString path_1 = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/data-1.0.sqlite";
    QFile file_1(path_1);

    if (file_1.exists()) {
        db.setDatabaseName(path_1);
        bool ok = open();
        if (!ok) {
            qDebug() << "Couldn't open db 1.0.";
            return ok;
        }
        QSqlQuery query;
        ok = query.exec("ALTER TABLE stopstable ADD COLUMN rank INTEGER");
        if (!ok) {
            qDebug() << "Upgrade from 1.0 failed." << lastError();
        }
        close();
        QString newName = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/data-2.0.sqlite";
        bool rename_ok = file_1.rename(newName);
        if (!rename_ok) qDebug() << "Rename failed";
        return ok && rename_ok;
    }
    return true;
}

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
        qDebug() << name << code << type << towards << latitude << longitude;
        if (!ret) {
            qDebug() << "***Adding " << name << " failed ***";
            qDebug() << lastError();
        }
        return ret;
    }
    else {
        qDebug() << "There is no db.";
        return false;
    }
}

//returns true if there are tubestations in stopstable
bool Database::areTubeStationsInDB() {
    if (createStopsTable()) {
        QSqlQuery query;
        bool ok = query.exec("SELECT * FROM stopstable WHERE type = 2");
        if (!ok) {
            qDebug() << lastError();
            return true; //raise error
        }
        query.last();
        if (query.at() < 0) { return false; }
        else return true;
    }
    else return true; //raise error
}

//deletes every entry in stopstable that is not set to favorite by user and returns true if successful otherwise returns fasle
bool Database::clearStopsTable() {
    QSqlQuery query;
    bool ok = query.exec("DELETE FROM stopstable WHERE favorite=0");
    return ok;
}

bool Database::importStations() {
    if (areTubeStationsInDB()) { return true; } //only need to import if we haven't got the data in our database
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/stations.csv";
    QFile file(path);
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error: stations.csv is not readable";
        }
        db.transaction();
        while (!file.atEnd()) {
            ///TODO Check for validity of file
            QByteArray line =  file.readLine();
            QList<QByteArray> lineList = line.split(';');
            if (createStopsTable() && lineList.size() >= 6 ) {
                QSqlQuery query;
                query.prepare("INSERT INTO stopstable (name, code, type, latitude, longitude, favorite) "
                              "VALUES (:name, :code, :type, :latitude, :longitude, :favorite)"
                              );

                if (lineList.at(0) == "name") continue; //skip first line
                query.bindValue(":name",lineList.at(0));
                QString code = lineList.at(1);
                if (code == "") {
                    //Null
                    query.bindValue(":code",QVariant(QVariant::String));
                }
                else { query.bindValue(":code",code); }
                query.bindValue(":type",lineList.at(2).toInt());
                query.bindValue(":latitude",lineList.at(4));
                query.bindValue(":longitude",lineList.at(5));
                query.bindValue(":favorite", 0);
                if (!query.exec()) {
                    qDebug() << "Error: query failed, rolling back transaction" << lastError();
                    db.rollback();
                    return false;
                }
            }
            else { qDebug() << "lineList.size()" << lineList.size(); }
        }
        db.commit();
        qDebug() << "Stations imported";
        return true;
    }
    else {
        qDebug() << "Error: There is no CSV file located";
        return false;
    }
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
    db.transaction();
    QSqlQuery query, query_incr;
    //incrementing all ranks so that fresh results stay on the top for better usability
    bool query_incr_ok = query_incr.exec("UPDATE stopstable SET rank = rank + 1 ");
    query.prepare("UPDATE stopstable SET favorite=1, rank= 1 WHERE code= :code ");
    query.bindValue(":code", code);
    bool query_ok = query.exec();
    if (query_incr_ok && query_ok) {
        db.commit();
        qDebug() << code << "is now favorite with rank 1";
        return true;
    }
    else{
        qDebug() << "makeFavorite() failed." << lastError();
        db.rollback();
        return false;
    }
}

bool Database::move(const QString& code1, const QString& code2) {
    int rank1 = getRank(code1);
    int rank2 = getRank(code2);
    if (!rank1) {
        qDebug() << code1 << "is not favorite, move is temporary";
        return true;
    } //user moved an item that is not a favorite, don't do anything
    db.transaction();
    QSqlQuery query_list, query_move;
    if (!rank2) {//shouldn't be possible
        qDebug() << "Error: Moving" << code1 << "before an item that is not a favorite!";
    }
    else {
        if (rank1 > rank2) {
            query_list.prepare("UPDATE stopstable SET rank = rank + 1 WHERE rank < :rank1 AND rank >= :rank2");
        }
        else {
            query_list.prepare("UPDATE stopstable SET rank = rank - 1 WHERE rank > :rank1 AND rank <= :rank2");
        }
        query_list.bindValue(":rank1",rank1);
        query_list.bindValue(":rank2",rank2);
        query_move.prepare("UPDATE stopstable SET rank = :rank2 WHERE code = :code1");
        query_move.bindValue(":rank2",rank2);
        query_move.bindValue(":code1",code1);
    }
    bool list_ok = query_list.exec();
    bool move_ok = query_move.exec();
    if (list_ok && move_ok) { db.commit(); }
    else {
        qDebug() << "Moving failed: " << lastError();
        db.rollback();
    }


    return list_ok && move_ok;
}

//makes a stop NOT favorite and decrements the ranks of other items to eliminate gaps,
//returns true on success and false otherwise
bool Database::unFavorite(const QString& code) {
    db.transaction();
    QSqlQuery query, query_dec;
    query_dec.prepare("UPDATE stopstable SET rank= rank - 1 WHERE rank > :current");
    query_dec.bindValue(":current", getRank(code));
    query.prepare("UPDATE stopstable SET favorite=0, rank=NULL WHERE code= :code ");
    query.bindValue(":code", code);
    bool query_dec_ok = query_dec.exec();
    bool query_ok = query.exec();
    if (query_dec_ok && query_ok) {
        db.commit();
        return true;
    }
    else{
        qDebug() << "unFavorite() failed." << lastError();
        db.rollback();
        return false;
    }
}
