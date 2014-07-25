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

