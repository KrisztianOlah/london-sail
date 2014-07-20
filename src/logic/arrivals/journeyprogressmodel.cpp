#include "journeyprogressmodel.h"
#include "journeyprogresscontainer.h"

JourneyProgressModel::JourneyProgressModel(QObject *parent) :
    QAbstractListModel(parent),
    container(static_cast<JourneyProgressContainer*>(parent))
{
}

void JourneyProgressModel::beginInsert(int first, int last) { beginInsertRows(QModelIndex(),first,last);}

void JourneyProgressModel::beginReset() { beginResetModel();}

QVariant JourneyProgressModel::data(const QModelIndex& index, int role) const {
    QPair<QString,double> item = container->at(index.row());
    switch (role) {
    case SortRole:
        return container->getDeltaTime(item.second);
    case EtaRole:
        return container->getEta(item.second);
    case StopNameRole:
        return item.first;
    }
    return QVariant();
}

void JourneyProgressModel::endInsert() { endInsertRows(); }

void JourneyProgressModel::endReset() { endResetModel();}

QHash<int,QByteArray> JourneyProgressModel::roleNames() const {
    QHash<int,QByteArray> roles;
    roles[SortRole] = "sortData";
    roles[EtaRole] = "etaData";
    roles[StopNameRole] = "stopNameData";
    return roles;
}

int JourneyProgressModel::rowCount(const QModelIndex& /*parent*/) const {
    if (container) { return container->size(); }
    else return 0;
}

