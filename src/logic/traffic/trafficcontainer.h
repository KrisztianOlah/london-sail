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
