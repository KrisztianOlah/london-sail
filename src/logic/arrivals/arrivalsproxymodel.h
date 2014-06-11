#ifndef ARRIVALSPROXYMODEL_H
#define ARRIVALSPROXYMODEL_H

#include <QSortFilterProxyModel>

class ArrivalsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ArrivalsProxyModel(QObject *parent = 0);
protected:
//    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

signals:

public slots:

};

#endif // ARRIVALSPROXYMODEL_H
