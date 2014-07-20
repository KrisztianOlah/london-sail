#include "arrivalsmodel.h"

#include "arrivalscontainer.h"
#include "vehicle.h"

ArrivalsModel::ArrivalsModel(ArrivalsContainer* c, QObject *parent) : QAbstractListModel(parent),
                                                                      container(c)
{
    container->registerModel(this);
}

void ArrivalsModel::beginInsert(int rows) { beginInsertRows(QModelIndex(),0,rows);}

//informs model that whatever is in the model is to be invalid
void ArrivalsModel::beginReset() { beginResetModel();}

QVariant ArrivalsModel::data(const QModelIndex& index, int role) const {
    Vehicle vehicle = container->at(index.row());
    switch (role) {
    case IdRole:
        return vehicle.id;
    case LineRole:
        return vehicle.line;
    case DestinationRole:
        return vehicle.destination;
    case EtaRole:
        return vehicle.eta;
    case TowardRole:
        return vehicle.towards;
    case PlatformRole:
        return vehicle.platform;
    default:
        return QVariant();
    }
}

void ArrivalsModel::endInsert() { endInsertRows(); }

void ArrivalsModel::endReset() { endResetModel();}

void ArrivalsModel::replaceContainer(const ArrivalsContainer& pOther) {
    container->replace(pOther);
}

QHash<int,QByteArray> ArrivalsModel::roleNames() const {
    QHash<int,QByteArray> roles;
    roles[IdRole] = "idData";//vehicle id for bus it's the registration number
    roles[LineRole] = "lineData";
    roles[DestinationRole] = "destinationData";
    roles[EtaRole] = "etaData";
    roles[TowardRole] = "towardData";
    roles[PlatformRole] = "platformData";
    return roles;
}

int ArrivalsModel::rowCount(const QModelIndex& /*parent*/) const {
    if (container) { return container->size(); }
    else return 0;
}




