#include "arrivalslogic.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QUrl>
#include "arrivals/arrivalsmodel.h"
#include "arrivals/arrivalsproxymodel.h"
#include "arrivals/arrivalscontainer.h"
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
                                                reply_arrivals(0),
                                                reply_busStop(0)
{
    arrivalsProxyModel->setSourceModel(arrivalsModel);
    arrivalsProxyModel->sort(0);
    connect(arrivalsTimer, SIGNAL(timeout()), this, SLOT(fetchArrivalsData()) );
}

//private:
//return LineName,DestinationName,EstimatedTime,VehicleID  //DestinationText for shorter text
//registration num must not start with X_or contain NEW in the first five letters
//it should return a model of buses containing the above data, refreshing it every 30 sec
void ArrivalsLogic::getBusArrivalsByCode(const QString& code) {
    QString stopCode = QString("StopCode1=") + code;
    QString returnList = "&ReturnList=LineName,DestinationName,EstimatedTime,VehicleID";
    QString request = baseUrl + stopCode +  returnList;

    QUrl url(request);
    reply_arrivals = networkMngr->get(QNetworkRequest(url));

    connect(reply_arrivals, SIGNAL(finished()), this, SLOT(onArrivalsDataReceived()) );
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
        bus.destination = (*(iter->array().begin() + 2)).toString();
        bus.id = (*(iter->array().begin() + 3)).toString();
        double delta = (*(iter->array().begin() + 4)).toDouble() - currentTime;
        double inSec = delta / 1000;
        double inMins = inSec / 60;
        //truncate to whole numbers
        bus.eta = inMins;
        tempContainer.add(bus);
    }
    arrivalsContainer->replace(tempContainer);
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

//public slots:
void ArrivalsLogic::clearArrivalsData() {
    clearCurrentStop();
    if (arrivalsContainer) {
        arrivalsContainer->clearData();
    }

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

void ArrivalsLogic::getBusStopsByName(const QString& /*name*/) {}

Stop* ArrivalsLogic::getCurrentStop() { return currentStop; }

void ArrivalsLogic::startArrivalsUpdate() {
    fetchArrivalsData();
    //it might be different for other kinds of stops!
    arrivalsTimer->start(30000);
}

void ArrivalsLogic::stopArrivalsUpdate() {
    qDebug() << "updating stopped.";
    arrivalsTimer->stop();
}
