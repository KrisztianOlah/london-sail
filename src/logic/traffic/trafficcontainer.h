#ifndef TRAFFICCONTAINER_H
#define TRAFFICCONTAINER_H

#include <QHash>
#include <QList>
#include <QObject>
#include "disruption.h"
#include "street.h"


class DisruptionModel;
class DisruptionProxyModel;
class StreetModel;

class TrafficContainer : public QObject
{
    Q_OBJECT
public:
    explicit TrafficContainer(QObject *parent = 0);
private:
    QList<Disruption> disruptions;
    DisruptionModel* disruptionModel;//Qt memory management
    DisruptionProxyModel* proxyModel;//Qt memory management
    StreetModel* streetModel;//Qt memory management
    QHash<int,Street> streets;
private:
    QList<Street>* getStreetsList(int id);
public:
    void addDisruption(const Disruption&);
    void addStreet(int id, const Street& street);
    QList<Disruption> getDisruptionList();
    DisruptionProxyModel* getDisruptionModel();
    StreetModel* getStreetModel(int id);
    int size();
    void swap(TrafficContainer& other);
signals:

public slots:

};

#endif // TRAFFICCONTAINER_H
