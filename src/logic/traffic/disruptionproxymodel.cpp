#include "disruptionproxymodel.h"
#include <QDebug>
#include "disruptionmodel.h"

DisruptionProxyModel::DisruptionProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool DisruptionProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const {
    QModelIndex index = sourceModel()->index(source_row,0,source_parent);
    QString status = sourceModel()->data(index,DisruptionModel::StatusRole).toString();
    QString location = sourceModel()->data(index,DisruptionModel::LocationRole).toString();
    return ((status == "Active Long Term" || status == "Active") && location.contains(filterRegExp()));
}

//public slots:
void DisruptionProxyModel::filter(const QString& str) {
    setFilterRegExp(QRegExp(str,Qt::CaseInsensitive,QRegExp::FixedString) );
}
//"Scheduled"
//"Recurring Works"
//"Recently Cleared"
