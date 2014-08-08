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


#include "arrivalslogic.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QUrl>
#include <cmath>
#include "arrivals/arrivalsmodel.h"
#include "arrivals/arrivalsproxymodel.h"
#include "arrivals/arrivalscontainer.h"
#include "arrivals/journeyprogresscontainer.h"
#include "arrivals/stop.h"
#include "arrivals/stopsquerymodel.h"
#include "arrivals/vehicle.h"
#include "database/databasemanager.h"

ArrivalsLogic::ArrivalsLogic(DatabaseManager* dbm, QObject* parent) : QObject(parent),
                                                activeStops("StopPointState=0"),
                                                arrivalsContainer(new ArrivalsContainer()),
                                                arrivalsModel(new ArrivalsModel(arrivalsContainer,this)),
                                                arrivalsProxyModel(new ArrivalsProxyModel(this)),
                                                arrivalsTimer(new QTimer(this)),
                                                baseUrl("http://countdown.api.tfl.gov.uk/interfaces/ura/instant_V1?"),
                                                databaseManager(dbm),
                                                currentStop(new Stop(databaseManager)),
                                                downloadingArrivals(false),
                                                downloadingJourneyProgress(false),
                                                downloadingListOfStops(false),
                                                downloadingStop(false),
                                                networkMngr(static_cast<QNetworkAccessManager*>(parent)),
                                                journeyProgressContainer(new JourneyProgressContainer(this)),
                                                journeyProgressTimer(new QTimer(this)),
                                                reply_arrivals(0),
                                                reply_busStop(0),
                                                reply_journeyProgress(0),
                                                reply_stops(0),
                                                stopsQueryModel(new StopsQueryModel(databaseManager))
{
    arrivalsProxyModel->setSourceModel(arrivalsModel);
    arrivalsProxyModel->sort(0);
    stopsQueryModel->showStops();

    connect(arrivalsTimer, SIGNAL(timeout()), this, SLOT(fetchArrivalsData()) );
    connect(journeyProgressTimer, SIGNAL(timeout()), this, SLOT(fetchJourneyProgress()) );
    connect(journeyProgressContainer, SIGNAL(dataChanged()), this, SLOT(onProgressDataChanged()) );
}

//private:
void ArrivalsLogic::clearArrivalsData() {
    if (arrivalsContainer) {
        arrivalsContainer->clearData();
    }

}

void ArrivalsLogic::clearJourneyProgressData() {
    currentBusDirectionId = "";
    setCurrentVehicleId("");
    journeyProgressContainer->clear();
}

//DestinationText for shorter text
//FIX registration num must not start with X_or contain NEW in the first five letters
void ArrivalsLogic::getBusArrivalsByCode(const QString& code) {
    QString stopCode = QString("StopCode1=") + code;
    QString returnList = "&ReturnList=LineName,DestinationName,EstimatedTime,RegistrationNumber,DirectionID";
    QString request = baseUrl + stopCode +  returnList;

    QUrl url(request);
    downloadingArrivals = true;
    downloadSatateChanged();
    reply_arrivals = networkMngr->get(QNetworkRequest(url));

    connect(reply_arrivals, SIGNAL(finished()), this, SLOT(onArrivalsDataReceived()) );
}

void ArrivalsLogic::getBusProgress(const QString& registrationNum) {
    QString regPart = QString("RegistrationNumber=") + registrationNum;
    QString directionIDPart = QString("&DirectionID=") + currentBusDirectionId;
    QString returnList = "&ReturnList=StopPointName,EstimatedTime";
    QString request = baseUrl + regPart + directionIDPart + returnList;
    QUrl url(request);
    downloadingJourneyProgress = true;
    downloadSatateChanged();
    reply_journeyProgress = networkMngr->get(QNetworkRequest(url));

    connect(reply_journeyProgress, SIGNAL(finished()), this, SLOT(onBusProgressReceived()) );
}

QList<QJsonDocument> ArrivalsLogic::makeDocument(QNetworkReply* reply) {
    QList<QJsonDocument> document;
    if (reply) {
        while (!reply->atEnd()) {
            document << QJsonDocument::fromJson(reply->readLine());
        }
        reply->deleteLater();
    }
    return document;
}

//private slots:
void ArrivalsLogic::fetchArrivalsData() {
    qDebug() << "updated";
    switch (currentStop->getType()) {
    case Stop::None:
        return;
    case Stop::Bus:
        getBusArrivalsByCode(currentStop->getID());
        return;
    case Stop::River:
        getBusArrivalsByCode(currentStop->getID());
        return;
    }
}

void ArrivalsLogic::fetchJourneyProgress() {
    if (currentVehicleId == "") return;
    //TODO switch on currentStop->type
    getBusProgress(currentVehicleId);
}

void ArrivalsLogic::onArrivalsDataReceived() {
    downloadingArrivals = false;
    downloadSatateChanged();
    QList<QJsonDocument> document = makeDocument(reply_arrivals);
    QList<QJsonDocument>::iterator first = document.begin();

    if (document.isEmpty()) return;//nothing to do
    //server time UTC in msec from Epoch at the time of request
    //use this to compare with expected arrival time, if device clock is not correctly set
    //the arrival times are still accurately presented to user
    double currentTime = (*(first->array().begin() +2)).toDouble();
    ArrivalsContainer tempContainer(arrivalsModel);
    for (QList<QJsonDocument>::iterator iter = first + 1; iter != document.end(); ++iter) {
        Vehicle bus;
        bus.line = (*(iter->array().begin() + 1)).toString();
        currentBusDirectionId =  QString::number((*(iter->array().begin() + 2)).toDouble());
        bus.destination = (*(iter->array().begin() + 3)).toString();
        bus.id = (*(iter->array().begin() + 4)).toString();//registration number
        double delta = (*(iter->array().begin() + 5)).toDouble() - currentTime;
        double inSec = delta / 1000;
        double inMins = inSec / 60;
        //round to whole numbers
        bus.eta = std::round(inMins);
        tempContainer.add(bus);
    }
    arrivalsContainer->replace(tempContainer);
}

void ArrivalsLogic::onBusProgressReceived() {
    downloadingJourneyProgress = false;
    downloadSatateChanged();
    qDebug() << "onBusProgressReceived() is called";
    QList<QJsonDocument> document = makeDocument(reply_journeyProgress);
    if (document.isEmpty()) return;//nothing to do
    double serverTime = (*(document.begin()->array().begin() +2)).toDouble();
    QList<QPair<QString, double>> list;
    for (QList<QJsonDocument>::iterator iter = document.begin() + 1; iter != document.end(); ++iter) {
        QPair<QString, double> pair;
        pair.first = (*(iter->array().begin() +1)).toString();
        pair.second = (*(iter->array().begin() +2)).toDouble();
        list.append(pair);
    }
    journeyProgressContainer->setTime(serverTime);
    journeyProgressContainer->refreshData(list);
}

void ArrivalsLogic::onBusStopDataReceived() {
    QList<QJsonDocument> document = makeDocument(reply_busStop);
    //only want the second array as the first one is the version array and there are only 2 arrays
    if (document.isEmpty()) {
        qDebug() << "QJsonDocument is empty.";
        return; //there is nothing to do
    }
    QList<QJsonDocument>::iterator dataArray = document.begin() + 1;
    if (dataArray->isArray()) {
        //id is set in ArrivalsLogic::getBusStopByCode(const QString&)
        currentStop->setName( (*(dataArray->array().begin() + 1)).toString() );
        currentStop->setTowards( (*(dataArray->array().begin() + 3)).toString() );
        currentStop->setStopPointIndicator( (*(dataArray->array().begin() + 4)).toString() );
        currentStop->setLatitude( (*(dataArray->array().begin() + 5)).toDouble() );
        currentStop->setLongitude( (*(dataArray->array().begin() + 6)).toDouble() );
        if ( (*(dataArray->array().begin() + 2)).toString() == QString("SLRS") ) {
            currentStop->setType(Stop::River);
        }
        else { currentStop->setType(Stop::Bus); }

        currentStop->updated();
        emit stopDataChanged();
    }
    else qDebug() << "Invalid QJsonArray";
    downloadingStop = false;
    downloadSatateChanged();
}

void ArrivalsLogic::onListOfBusStopsReceived() {
    QList<QJsonDocument> document = makeDocument(reply_stops);
    if (document.size() < 1 ) return; //if empty or only have version array then nothing to do
    //skip version array
    for (QList<QJsonDocument>::const_iterator iter = document.begin() + 1;iter != document.end();++iter) {
        Stop stop(databaseManager);
        stop.setName((*(iter->array().begin() + 1)).toString());
        stop.setID((*(iter->array().begin() + 2)).toString());
        stop.setTowards((*(iter->array().begin() + 4)).toString());
        stop.setStopPointIndicator((*(iter->array().begin() + 5)).toString());
        stop.setLatitude((*(iter->array().begin() + 6)).toDouble());
        stop.setLongitude((*(iter->array().begin() + 7)).toDouble());
        QString stopPointType = (*(iter->array().begin() + 3)).toString();
        if ( stopPointType == QString("SLRS")) {
            stop.setType(Stop::River);
        }
        else {
            stop.setType(Stop::Bus);
        }
        //The meaning of these codes are documented in the Bus arrivals API documentation
        //only display sstops with these codes
        if (stopPointType == "STBR" || stopPointType == "STBC" || stopPointType == "SRVA" ||
            stopPointType == "STZZ" || stopPointType == "STBN" || stopPointType == "SLRS" ||
            stopPointType == "STBS" || stopPointType == "STSS") {

            //to prevent a bug when server returns a stop where code isNull() ie: Hammersmith Bus Station
            if (!(*(iter->array().begin() + 2)).isNull()) { stop.addToDb(); }
        }
    }
    stopsQueryModel->showStops();
    downloadingListOfStops = false;
    downloadSatateChanged();
}

void ArrivalsLogic::onProgressDataChanged() {
    qDebug() << " NextStopChanged()";
    emit nextStopChanged();
}

//public slots:
void ArrivalsLogic::clearCurrentStop() { currentStop->clear();}

bool ArrivalsLogic::favorStop(const QString& code, bool b) {
    if (b) {
        return databaseManager->makeFavorite(code);
    }
    else return databaseManager->unFavorite(code);
}

ArrivalsProxyModel* ArrivalsLogic::getArrivalsModel() { return arrivalsProxyModel; }

void ArrivalsLogic::getBusStopByCode(const QString& code) {
    currentStop->setID(code);

    QString stopcode = QString("StopCode1=") + code;
    QString returnList = "&ReturnList=StopPointName,Towards,StopPointIndicator,StopPointType,Latitude,Longitude";
    QString request = baseUrl + stopcode + returnList;
    QUrl url(request);
    downloadingStop = true;
    downloadSatateChanged();
    reply_busStop = networkMngr->get(QNetworkRequest(url));

    connect(reply_busStop, SIGNAL(finished()), this, SLOT(onBusStopDataReceived()) );
}

void ArrivalsLogic::getBusStopsByName(const QString& name) {
    QString stopPointName = QString("StopPointName=") + name;
    QString returnList = "&ReturnList=StopPointName,StopCode1,Towards,StopPointIndicator,StopPointType,Latitude,Longitude";
    QString request = baseUrl + stopPointName + returnList;
    QUrl url = request;
    downloadingListOfStops = true;
    downloadSatateChanged();
    reply_stops = networkMngr->get(QNetworkRequest(url) );
    connect(reply_stops, SIGNAL(finished()), this, SLOT(onListOfBusStopsReceived()) );
}

QString ArrivalsLogic::getCurrentDestination() const { return currentDestination;}

Stop* ArrivalsLogic::getCurrentStop() { return currentStop; }

QString ArrivalsLogic::getCurrentVehicleLine() const { return currentVehicleLine; }

bool ArrivalsLogic::isDownloadingArrivals() const { return downloadingArrivals; }

bool ArrivalsLogic::isDownloadingJourneyProgress() const { return downloadingJourneyProgress; }

bool ArrivalsLogic::isDownloadingListOfStops() const { return downloadingListOfStops; }

bool ArrivalsLogic::isDownloadingStop() const { return downloadingStop; }

ArrivalsProxyModel* ArrivalsLogic::getJourneyProgressModel() { return journeyProgressContainer->getModel(); }

QString ArrivalsLogic::getNextStop() { return journeyProgressContainer->getNextStop().first; }

StopsQueryModel* ArrivalsLogic::getStopsQueryModel() { return stopsQueryModel; }

bool ArrivalsLogic::isStopFavorite(const QString& code) { return databaseManager->isFavorite(code); }

void ArrivalsLogic::setCurrentDestination(const QString& destination) { currentDestination = destination; }

void ArrivalsLogic::setCurrentVehicleId(const QString& id) { currentVehicleId = id;}

void ArrivalsLogic::setCurrentVehicleLine(const QString& line) { currentVehicleLine = line; }

void ArrivalsLogic::startArrivalsUpdate() {
    fetchArrivalsData();
    //it might be different for other kinds of stops!
    arrivalsTimer->start(30000);
}

void ArrivalsLogic::startJourneyProgressUpdate() {
    qDebug() << "***startJourneyProgressUpdate() ***";
    fetchJourneyProgress();
    journeyProgressTimer->start(30000);
}

void ArrivalsLogic::stopArrivalsUpdate() {
    qDebug() << "updating stopped.";
    arrivalsTimer->stop();
    clearArrivalsData();
}

void ArrivalsLogic::stopJourneyProgressUpdate() {
    journeyProgressTimer->stop();
    clearJourneyProgressData();
}

