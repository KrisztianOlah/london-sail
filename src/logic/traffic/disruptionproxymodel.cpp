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

#include "disruptionproxymodel.h"
#include <QDebug>
#include "disruptionmodel.h"

DisruptionProxyModel::DisruptionProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    statusFilter("Traffic Disruptions")
{
}

//rules what to filter
bool DisruptionProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const {
    QModelIndex index = sourceModel()->index(source_row,0,source_parent);
    QString status = sourceModel()->data(index,DisruptionModel::StatusRole).toString();
    QString location = sourceModel()->data(index,DisruptionModel::LocationRole).toString();
    if (statusFilter == "Traffic Disruptions") {
        return ((status == "Active Long Term" || status == "Active") && location.contains(filterRegExp()));
    }
    else return ((status == statusFilter) && location.contains(filterRegExp()));

}

//public slots:
//user defined filter
void DisruptionProxyModel::filter(const QString& str) {
    currentFilter = str;
    setFilterRegExp(QRegExp(str,Qt::CaseInsensitive,QRegExp::FixedString) );
}

bool DisruptionProxyModel::isFilterEmptyString() {return currentFilter == "";}

void DisruptionProxyModel::setStatusFilter(const QString& str) {
    statusFilter = str;
    invalidateFilter();
}
