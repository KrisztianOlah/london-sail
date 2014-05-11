#include "disruptionmodel.h"
#include <QDebug>
#include "disruption.h"
#include "trafficcontainer.h"

// !!! See notes on parent in the header !!!
DisruptionModel::DisruptionModel(QObject* c) : container(static_cast<TrafficContainer*>(c))
{
}

void DisruptionModel::beginInsert(int rows) { beginInsertRows(QModelIndex(),0,rows);}

void DisruptionModel::beginReset() { beginResetModel();}

QVariant DisruptionModel::data(const QModelIndex& index, int role) const {
    if (container) {
        QList<Disruption> list(container->getDisruptionList());
        switch (role) {
        case IDRole:
            return list.at(index.row()).id;
        case StatusRole:
            return list.at(index.row()).status;
        case SeverityRole:
            return list.at(index.row()).severity;
        case LevelOfInterestRole:
            return list.at(index.row()).levelOfInterest;
        case LocationRole:
            return list.at(index.row()).location;
        case CategoryRole:
            return list.at(index.row()).category;
        case SubCategoryRole:
            return list.at(index.row()).subCategory;
        case StartTimeRole:
            return list.at(index.row()).startTime;
        case CommentsRole:
            return list.at(index.row()).comments;
        case CurrentUpdateRole:
            return list.at(index.row()).currentUpdate;
        }
    }
    else qDebug() << "container is nullptr";
    return QVariant();
}

void DisruptionModel::endInsert() { endInsertRows(); }

void DisruptionModel::endReset() { endResetModel();}

QHash<int,QByteArray> DisruptionModel::roleNames() const {
    QHash<int,QByteArray> roles;
    roles[IDRole] = "idData";
    roles[StatusRole] = "statusData";
    roles[SeverityRole] = "severityData";
    roles[LevelOfInterestRole] = "levelOfInterestData";
    roles[LocationRole] = "locationData";
    roles[CategoryRole] = "categoryData";
    roles[SubCategoryRole] = "subCategoryData";
    roles[StartTimeRole] = "startTimeData";
    roles[CommentsRole] = "commentsData";
    roles[CurrentUpdateRole] = "currentUpdateData";

    return roles;
}


int DisruptionModel::rowCount(const QModelIndex& /*parent*/) const {
    if (container) { return container->size(); }
    else return 0;
}
