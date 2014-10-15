#include "mapsmodel.h"

MapsModel::MapsModel(QList<BusMap>* pL, QObject* parent) : QAbstractListModel(parent),
                                                           pList(pL)
{
}

//Adds a new BusMap in the list
void MapsModel::addMap(const BusMap& map) {
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    pList->append(map);
    endInsertRows();
}

//Clears list and model
void MapsModel::clearData() {
    beginResetModel();
    pList->clear();
    endResetModel();
}

QVariant MapsModel::data(const QModelIndex& index, int role) const {
    switch (role) {
    case NameRole:
        return pList->at(index.row()).name;
    case LinkRole:
        return pList->at(index.row()).link;
    default:
        return QVariant();
    }
}

QHash<int,QByteArray> MapsModel::roleNames() const {
    QHash<int,QByteArray> roles;

    roles[NameRole] = "nameData";
    roles[LinkRole] = "linkData";
    return roles;
}

int MapsModel::rowCount(const QModelIndex& /*parent*/) const {
    if (pList) {
        return pList->size();
    }
    else return 0;
}
