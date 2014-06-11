#include "arrivalsproxymodel.h"
#include "arrivalsmodel.h"

ArrivalsProxyModel::ArrivalsProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSortRole(ArrivalsModel::EtaRole);
}

//virtual bool ArrivalsProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const {
//    //
//}
