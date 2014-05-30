#include "trafficcontainer.h"
#include <QDebug>
#include "disruptionmodel.h"
#include "disruptionproxymodel.h"
#include "streetmodel.h"

TrafficContainer::TrafficContainer(QObject *parent) :
    QObject(parent),
    disruptionModel(new DisruptionModel(this)),
    proxyModel(new DisruptionProxyModel(this)),
    streetModel(0)
{
    proxyModel->setSourceModel(disruptionModel);
}

//private:
QList<Street>* TrafficContainer::getStreetsList(int id) {
    QList<Street>* list = new QList<Street>();
    QHash<int,Street>::const_iterator iter = streets.find(id);
    while (iter != streets.end() && iter.key() == id) {
        *list << (iter++).value();
    }
    return list;
}

//public:
//this should not be used direcly whilst connected to a model, see this->swap()
void TrafficContainer::addDisruption(const Disruption& item) {
    disruptions << item;
}

//this should not be used direcly whilst connected to a model, see this->swap()
void TrafficContainer::addStreet(int id, const Street& street) {
    if (id) {
        streets.insertMulti(id,street);
    }
}

QList<Disruption> TrafficContainer::getDisruptionList() { return disruptions;}

DisruptionProxyModel* TrafficContainer::getDisruptionModel() { return proxyModel; }

StreetModel* TrafficContainer::getStreetModel(int id) {
    QList<Street>* list = getStreetsList(id);
    //delete old data from memory
    if (streetModel) {
        delete streetModel;
        streetModel = 0;
    }
    streetModel = new StreetModel(list, this);
    return streetModel;
}


int TrafficContainer::size() { return disruptions.size(); }

void TrafficContainer::swap(TrafficContainer& other) {
    disruptionModel->beginReset();
    disruptions.clear();
    disruptionModel->endReset();

    disruptionModel->beginInsert(other.size()-1);//row numbers start with 0
    disruptions.swap(other.disruptions);
    disruptionModel->endInsert();

    //don't need to reset model as it will not become invalid until new model is requested
    streets.swap(other.streets);
}
