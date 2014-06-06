#include "servicestatusproxymodel.h"
#include "thisweekendlinemodel.h"

ServiceStatusProxyModel::ServiceStatusProxyModel(QObject* parent) :
    QSortFilterProxyModel(parent)
{
    setSortRole(ThisWeekendLineModel::NameRole);
}
