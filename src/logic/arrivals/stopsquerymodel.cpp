#include "stopsquerymodel.h"
#include <QDebug>
#include <QHash>
#include <QSqlRecord>
#include "../database/databasemanager.h"

extern DatabaseManager databaseManager;

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
    return roles;
}

void StopsQueryModel::showStops() { setQuery("SELECT * FROM stopstable");}

//public slots:
void StopsQueryModel::clearStops() {
    if (databaseManager) {
        bool ok = databaseManager->clearStopsTable();
        if (!ok) { qDebug() << "clearing stopstable failed"; }
        else qDebug() << "cleared stopstable";
        showStops();
    }
}
