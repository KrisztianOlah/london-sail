/*
Copyright (C) 2014 Krisztian Olah

  email: fasza2mobile@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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
