#include "arrivalsproxymodel.h"
#include "arrivalsmodel.h"

ArrivalsProxyModel::ArrivalsProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSortRole(ArrivalsModel::EtaRole);
}
