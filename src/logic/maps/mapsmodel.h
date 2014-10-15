#ifndef MAPSMODEL_H
#define MAPSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "busmap.h"

//Model to contain a list of downloadable maps' name and corresponding link for an area or route
class MapsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MapRoles { NameRole = Qt::UserRole, LinkRole };
    explicit MapsModel(QList<BusMap>* pList = 0,QObject* parent = 0);
private:
    QList<BusMap>* pList;
public:
    void addMap(const BusMap&);
    void clearData();
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex() ) const;
};

#endif // MAPSMODEL_H
