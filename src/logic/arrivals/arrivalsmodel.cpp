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

#include "arrivalsmodel.h"
#include "arrivalscontainer.h"
#include "vehicle.h"

#include <QDebug>

ArrivalsModel::ArrivalsModel(ArrivalsContainer* c, QObject *parent) : QAbstractListModel(parent),
                                                                      container(c)
{
    container->registerModel(this);
}

void ArrivalsModel::beginInsert(int rows) { beginInsertRows(QModelIndex(),0,rows);}

void ArrivalsModel::beginRemove() {
    beginRemoveRows(QModelIndex(),0,rowCount() -1);
}

//informs model that whatever is in the model is to be invalid
void ArrivalsModel::beginReset() {
    beginResetModel();
}

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
    case TypeRole:
        return vehicle.type;
    case PlatformRole:
        return vehicle.platform;
    default:
        return QVariant();
    }
}

void ArrivalsModel::endInsert() { endInsertRows(); }

void ArrivalsModel::endRemove() {
    endRemoveRows();
}

void ArrivalsModel::endReset() {
    endResetModel();
}

//swaps its container for another
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
    roles[TypeRole] = "typeData";
    roles[PlatformRole] = "platformData";
    return roles;
}

int ArrivalsModel::rowCount(const QModelIndex& /*parent*/) const {
    if (container) { return container->size(); }
    else return 0;
}

//public slots:
void ArrivalsModel::refresh() {
    beginReset();
    beginInsertRows(QModelIndex(),0,rowCount() -1);
    endInsertRows();
    endReset();
}



