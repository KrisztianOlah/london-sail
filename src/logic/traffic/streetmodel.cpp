#include "streetmodel.h"

StreetModel::StreetModel(QList<Street>* s,QObject* parent) : QAbstractListModel(parent),
                                                             streets(s)
{
}

QVariant StreetModel::data(const QModelIndex& index, int role) const {
    switch (role) {
    case NameRole:
        return streets->at(index.row()).name;
    case ClosureRole:
        return streets->at(index.row()).closure;
    case DirectionsRole:
        return streets->at(index.row()).directions;
    }
    return QVariant();
}

QHash<int,QByteArray> StreetModel::roleNames() const {
    QHash<int,QByteArray> roles;
    roles[NameRole] = "nameData";
    roles[ClosureRole] = "closureData";
    roles[DirectionsRole] = "directionsData";
    return roles;
}

int StreetModel::rowCount(const QModelIndex& /*parent*/) const {
    if (streets) { return streets->size(); }
    else return 0;
}

//public slots:
int StreetModel::count() { return rowCount(); }
