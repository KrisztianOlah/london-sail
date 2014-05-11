#ifndef STREETMODEL_H
#define STREETMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "street.h"

class StreetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit StreetModel(QList<Street>* streetsList = 0,QObject* parent = 0);
    enum StreetRole { NameRole, ClosureRole, DirectionsRole };
private:
    QList<Street>* streets;
public:
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex() ) const;
public slots:
    int count();
};

#endif // STREETMODEL_H
