#ifndef SERVICESTATUSPROXYMODEL_H
#define SERVICESTATUSPROXYMODEL_H

#include <QSortFilterProxyModel>

class ServiceStatusProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ServiceStatusProxyModel(QObject* parent = 0);
};

#endif // SERVICESTATUSPROXYMODEL_H
