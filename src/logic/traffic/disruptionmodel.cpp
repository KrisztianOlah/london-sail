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
