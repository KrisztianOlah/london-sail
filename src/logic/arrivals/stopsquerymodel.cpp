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


#include "stopsquerymodel.h"
#include <QDebug>
#include <QHash>
#include <QSqlRecord>
#include <QSqlQuery>
#include "../database/databasemanager.h"
#include "stop.h"

extern DatabaseManager databaseManager;

// !!! See header for note on parent !!!
StopsQueryModel::StopsQueryModel(QObject *parent) : QSqlQueryModel(parent),
                                                    databaseManager(static_cast<DatabaseManager*>(parent))
{
}

//public:
QVariant StopsQueryModel::data(const QModelIndex& index, int role) const {
    if(role <= Qt::UserRole)
                return QSqlQueryModel::data(index, role);
    QSqlRecord rec = record(index.row());

    switch (role) {
    case NameRole:
        return rec.value("name").toString();
    case CodeRole:
        return rec.value("code");
    case TypeRole:
        return rec.value("type").toInt();
    case TowardsRole:
        return rec.value("towards");
    case LatitudeRole:
        return rec.value("latitude").toDouble();
    case LongitudeRole:
        return rec.value("longitude").toDouble();
    case StopPointIndicatorRole:
        return rec.value("stoppointindicator");
    case RankRole:
        return rec.value("rank");
    default:
        return QVariant();
    }
}

QHash<int,QByteArray> StopsQueryModel::roleNames() const {
    QHash<int,QByteArray> roles;
    roles[NameRole] = "nameData";
    roles[CodeRole] = "codeData";
    roles[TypeRole] = "typeData";
    roles[TowardsRole] = "towardsData";
    roles[LatitudeRole] = "LatitudeData";
    roles[LongitudeRole] = "longitudeData";
    roles[StopPointIndicatorRole] = "stopPointIndicatorData";
    roles[RankRole] = "rankData";
    return roles;
}

void StopsQueryModel::showStops(int type) {
    qDebug() << "Showstops with type" << type;
    setQuery("SELECT * FROM stopstable WHERE type = 1 ORDER BY rank");
    if (type) {
//        QString query = QString("SELECT * FROM stopstable WHERE type = ") + QString::number(type) + QString(" OR favorite = 1 ORDER BY rank");
//        qDebug() << query;
//        setQuery(query);
    }
    else { setQuery("SELECT * FROM stopstable ORDER BY rank"); }

}

//public slots:
//clears the database from stops from stopstable that are not set as favorite
//this does//will not affect underground stations
void StopsQueryModel::clearStops() {
    if (databaseManager) {
        bool ok = databaseManager->clearStopsTable();
        if (!ok) { qDebug() << "clearing stopstable failed"; }
        else qDebug() << "cleared stopstable";
        showStops(Stop::Bus);
    }
}

QVariant StopsQueryModel::codeAt(int index) const {
    return record(index).value("code");
}

bool StopsQueryModel::move(int from, int to) {
    qDebug() << "Moving index" << from << "to" << to;
    if (from == to) return true; //no move is required
    bool ok = databaseManager->move(record(from).value("code").toString(), record(to).value("code").toString());
    query().exec();
    return ok;
}
