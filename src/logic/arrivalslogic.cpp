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
#include "arrivals/vehicle.h"


ArrivalsLogic::ArrivalsLogic(QObject *parent) : QObject(parent),
                                                activeStops("StopPointState=0"),
                                                arrivalsContainer(new ArrivalsContainer()),
                                                arrivalsModel(new ArrivalsModel(arrivalsContainer,this)),
                                                arrivalsProxyModel(new ArrivalsProxyModel(this)),
                                                arrivalsTimer(new QTimer(this)),
                                                baseUrl("http://countdown.api.tfl.gov.uk/interfaces/ura/instant_V1?"),
                                                currentStop(new Stop(this)),
                                                networkMngr(static_cast<QNetworkAccessManager*>(parent)),
                                                journeyProgressContainer(new JourneyProgressContainer(this)),
                                                journeyProgressTimer(new QTimer(this)),
                                                reply_arrivals(0),
                                                reply_busStop(0),
                                                reply_journeyProgress(0)
{
    arrivalsProxyModel->setSourceModel(arrivalsModel);
    arrivalsProxyModel->sort(0);
    connect(arrivalsTimer, SIGNAL(timeout()), this, SLOT(fetchArrivalsData()) );
    connect(journeyProgressTimer, SIGNAL(timeout()), this, SLOT(fetchJourneyProgress()) );
    connect(journeyProgressContainer, SIGNAL(dataChanged()), this, SLOT(onProgressDataChanged()) );
}

//private:
//VisitNumber,DirectionID
//return LineName,DestinationName,EstimatedTime,VehicleID//RegistrationNumber  //DestinationText for shorter text
//FIX registration num must not start with X_or contain NEW in the first five letters
void ArrivalsLogic::getBusArrivalsByCode(const QString& code) {
    QString stopCode = QString("StopCode1=") + code;
    QString returnList = "&ReturnList=LineName,DestinationName,EstimatedTime,RegistrationNumber,DirectionID";
    QString request = baseUrl + stopCode +  returnList;

    QUrl url(request);
    reply_arrivals = networkMngr->get(QNetworkRequest(url));

    connect(reply_arrivals, SIGNAL(finished()), this, SLOT(onArrivalsDataReceived()) );
}

void ArrivalsLogic::getBusProgress(const QString& registrationNum) {
    QString regPart = QString("RegistrationNumber=") + registrationNum;
    QString directionIDPart = QString("&DirectionID=") + currentBusDirectionId;
    QString returnList = "&ReturnList=StopPointName,EstimatedTime";
    QString request = baseUrl + regPart + directionIDPart + returnList;
    QUrl url(request);
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
    }

}

void ArrivalsLogic::fetchJourneyProgress() {
    if (currentVehicleId == "") return;
    //TODO switch on currentStop->type
    getBusProgress(currentVehicleId);
}

void ArrivalsLogic::onArrivalsDataReceived() {
    QList<QJsonDocument> document = makeDocument(reply_arrivals);
    QList<QJsonDocument>::iterator first = document.begin();

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
    QList<QJsonDocument> document = makeDocument(reply_journeyProgress);

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
        currentStop->setType(Stop::Bus);

        currentStop->updated();
        emit stopDataChanged();
    }
    else qDebug() << "Invalid QJsonArray";
}

void ArrivalsLogic::onProgressDataChanged() {
    emit nextStopChanged();
}
//public slots:
void ArrivalsLogic::clearArrivalsData() {
    clearCurrentStop();
    if (arrivalsContainer) {
        arrivalsContainer->clearData();
    }

}

void ArrivalsLogic::clearJourneyProgressData() {
    currentBusDirectionId = "";
    setCurrentVehicleId("");
    journeyProgressContainer->clear();
}

void ArrivalsLogic::clearCurrentStop() { currentStop->clear();}

ArrivalsProxyModel* ArrivalsLogic::getArrivalsModel() { return arrivalsProxyModel; }

void ArrivalsLogic::getBusStopByCode(const QString& code) {
    currentStop->setID(code);

    QString stopcode = QString("StopCode1=") + code;
    QString returnList = "&ReturnList=StopPointName,Towards,StopPointIndicator,StopPointType,Latitude,Longitude";
    QString request = baseUrl + stopcode + returnList;
    QUrl url(request);
    reply_busStop = networkMngr->get(QNetworkRequest(url));

    connect(reply_busStop, SIGNAL(finished()), this, SLOT(onBusStopDataReceived()) );
}

void ArrivalsLogic::getBusStopsByName(const QString& /*name*/) {
    ////////////
}

QString ArrivalsLogic::getCurrentDestination() const { return currentDestination;}

Stop* ArrivalsLogic::getCurrentStop() { return currentStop; }

QString ArrivalsLogic::getCurrentVehicleLine() const { return currentVehicleLine; }

ArrivalsProxyModel* ArrivalsLogic::getJourneyProgressModel() { return journeyProgressContainer->getModel(); }

QString ArrivalsLogic::getNextStop() { return journeyProgressContainer->getNextStop().first; }

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

