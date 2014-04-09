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

#include "thisweekendlinemodel.h"
#include <QDebug>

ThisWeekendLineModel::ThisWeekendLineModel(QObject *parent) :
    QAbstractListModel(parent)
{
}
//adds a new Tube Line to be displayed
void ThisWeekendLineModel::addLine(const Line& line) {
    int row = rowCount();
    beginInsertRows(QModelIndex(),row,row);
    lines.append(line);
    endInsertRows();
}
//retrives data by roles
QVariant ThisWeekendLineModel::data(const QModelIndex& index, int role) const {
    Line line(lines.at(index.row()));
    switch (role) {
    case NameRole:
        return line[Line::Name];
    case StatusRole:
        return line[Line::Status];
    case MessageRole:
        return line[Line::Message];
    case ColourRole:
        return line[Line::Colour];
    case BackgroundRole:
        return line[Line::Background];
    default:
        return QVariant();
    }
}

QHash<int,QByteArray> ThisWeekendLineModel::roleNames() const {
    QHash<int,QByteArray> roles;
    roles[NameRole] = "nameData";
    roles[StatusRole] = "statusData";
    roles[MessageRole] = "messageData";
    roles[ColourRole] = "colorData";
    roles[BackgroundRole] = "backgroundData";
    return roles;
}

//to be called when fetching new data, we don't need duplicates in the model
void ThisWeekendLineModel::reset() {
    beginRemoveRows(QModelIndex(),0,rowCount());
    lines.clear();
    endRemoveRows();
}

int ThisWeekendLineModel::rowCount(const QModelIndex& /*parent*/) const { return lines.size(); }
