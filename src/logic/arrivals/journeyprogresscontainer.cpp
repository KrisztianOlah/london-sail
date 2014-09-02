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

#include "journeyprogresscontainer.h"
#include <QDebug>
#include <cmath>
#include "arrivalsproxymodel.h"
#include "journeyprogressmodel.h"

//custom search algorithms because Qt algorithms are not sufficent and labmbdas or bind is not available in C++03 to use std algorithms
namespace {
typedef QList<QPair<QString,double> > StopList;
StopList::const_iterator find(StopList::const_iterator begin,StopList::const_iterator end, const QString& val) {
    for (StopList::const_iterator iter = begin; iter != end; ++iter) {
        if (iter->first == val) return iter;
    }
    return end;
}

StopList::iterator find(StopList::iterator begin,StopList::iterator end, const QString& val) {
    for (StopList::iterator iter = begin; iter != end; ++iter) {
        if (iter->first == val) return iter;
    }
    return end;
}

//given a StopList container a time value and a current time value it returns the first element where
//the elements time is less than the given time but more than the current time given
//any other case it just returns end() iterator
StopList::const_iterator findNextStop(StopList::const_iterator begin,StopList::const_iterator end, double val, double time) {
    for (StopList::const_iterator iter = begin; iter != end; ++iter) {
        if (iter->second - time > 0 && iter->second < val) return iter;
    }
    return end;
}

}//end of unnamed namespace

JourneyProgressContainer::JourneyProgressContainer(QObject* parent) : QObject(parent),
                                                                      model(new JourneyProgressModel(this)),
                                                                      proxyModel(new ArrivalsProxyModel(this))
{
    proxyModel->setSourceModel(model);
    proxyModel->sort(0);
}

//public:
QPair<QString,double> JourneyProgressContainer::at(int index) const { return data.at(index); }

//clears data and notifies model
void JourneyProgressContainer::clear() {
    model->beginReset();
    data.clear();
    model->endReset();
}

//counts difference between 2 datetime objects in sec or millisec
//time is server time saved when downloading the data from server
double JourneyProgressContainer::getDeltaTime(double prediction) const {
    double delta = prediction - time;
    return delta;
}


//for a given datetime object it calculates the difference between
//server time and arg and returns it in minutes
int JourneyProgressContainer::getEta(double prediction) const {
    double deltaInMilliSec = getDeltaTime(prediction);
    double deltaInSec = deltaInMilliSec /1000;
    double deltaInMin = deltaInSec / 60;
    int deltaRound = std::round(deltaInMin);
    return deltaRound;
}

ArrivalsProxyModel* JourneyProgressContainer::getModel() { return proxyModel; }

//Returns the next stop where vehicle is scheduled to stop
QString JourneyProgressContainer::getNextStop() const {
    QList<QPair<QString,double> >::const_iterator smallestSoFar = data.begin(), iter = data.begin();
    while (iter < data.end()) {
        smallestSoFar = iter;
        iter = findNextStop(iter,data.end(),smallestSoFar->second,time);
    }
    if (smallestSoFar != data.end()) {
        double eta = smallestSoFar->second;
        double theTime = time;
        if (eta - theTime < 0) {
            return QString("TERMINATED");
        }
        else return smallestSoFar->first;
    }

    else {
        return QString("NOT AVAILABLE");
    }
}

//it is called when new data is available, it appends the container with the new stop-eta pairs only
//if they are not already present otherwise just update eta to the new value,
//old data is not deleted until user changes the vehicle to track
//not using a QMap/QHash, because it needs random access iterators for model
void JourneyProgressContainer::refreshData(QList<QPair<QString,double> > list) {
    //check if other element is in data if yes update if no then set to 0 or delete
    if (!data.empty()) {
        model->beginReset();
        //check if some elements are already part of data, then just update them with a new time(double)
        for (QList<QPair<QString,double> >::iterator iter = data.begin();iter != data.end(); ++iter) {
            QList<QPair<QString,double> >::iterator match = find(list.begin(),list.end(),iter->first);
            //if both contain the same Stop then update to the new eta in data and then remove item from list
            if (match != list.end()) {
                iter->second = match->second;
                list.removeAt(match-list.begin());
            }
        }
        model->endReset();
    }
    //any (remaining)elements of list that wasn't/isn't in data will now be inserted if list is empty then nothing to do
    if (list.size() ) {
        model->beginInsert(data.size(),data.size() + list.size()-1);
        for (QList<QPair<QString,double> >::const_iterator iter = list.begin();iter != list.end(); ++iter) {
            data.append(*iter);
        }
        model->endInsert();
    }
    emit dataChanged();
}


void JourneyProgressContainer::setTime(double t) { time = t; }

int JourneyProgressContainer::size() const { return data.size(); }

