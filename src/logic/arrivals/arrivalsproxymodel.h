#ifndef ARRIVALSPROXYMODEL_H
#define ARRIVALSPROXYMODEL_H

#include <QSortFilterProxyModel>

class ArrivalsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ArrivalsProxyModel(QObject *parent = 0);
};

#endif // ARRIVALSPROXYMODEL_H
