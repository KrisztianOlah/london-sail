#include "trafficlogic.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlInputSource>
#include <QXmlSimpleReader>

//#include "traffic/disruptionmodel.h"//????
#include "traffic/disruptionproxymodel.h"
#include "traffic/trafficcontainer.h"
#include "traffic/trafficxmlhandler.h"

// !!! See header for note on parent !!!
TrafficLogic::TrafficLogic(QObject *parent) :
    QObject(parent),
    container(new TrafficContainer()),
    downloading(false),
    networkMngr(static_cast<QNetworkAccessManager*>(parent)),
    parsing(false),
    reply(0),
    url("http://data.tfl.gov.uk/tfl/syndication/feeds/tims_feed.xml?app_id=663a8a04&app_key=a1f29a8c881ffd777431a7cecf6c2d3b")
{
}

//private:
void TrafficLogic::parseData(const QByteArray& data) {
    QXmlSimpleReader xmlReader;
    QScopedPointer<QXmlInputSource> source(new QXmlInputSource());
    source->setData(data);
    QScopedPointer<TrafficContainer> workContainer(new TrafficContainer());
    QScopedPointer<TrafficXmlHandler> handler(new TrafficXmlHandler(workContainer.data()));
    xmlReader.setContentHandler(handler.data());
    xmlReader.setErrorHandler(handler.data());

    bool ok = false;
    ok = xmlReader.parse(source.data());
    if (ok) {
        container->swap(*(workContainer.data()) );
        qDebug() << "Traffic data has been parsed successfuly.";
    }
    else {
        qDebug() << "Parsing traffic data has failed.";
    }
    parsing = false;
    emit stateChanged();
}

//private slots:
void TrafficLogic::downloaded() {
    parsing = true;
    downloading = false;
    emit stateChanged();
    parseData(reply->readAll());
    reply->deleteLater();

}

//Tfl doesn't set Content-Length in the header so there is no way of knowing what percentage is complete
void TrafficLogic::progressSlot(qint64 bytesRecieved, qint64 /*bytesTotal*/) {
    emit downloadProgress(bytesRecieved);
}

//public slots:
DisruptionProxyModel* TrafficLogic::getDisruptionModel() { return container->getDisruptionModel(); }

StreetModel* TrafficLogic::getStreetModel(int id) { return container->getStreetModel(id); }

bool TrafficLogic::isDownloading() { return downloading; }

bool TrafficLogic::isParsing() { return parsing; }

void TrafficLogic::refresh() {
    if (networkMngr) {
        reply = networkMngr->get(QNetworkRequest(url));
        downloading = true;
        emit stateChanged();

        connect(reply, SIGNAL(finished()), this, SLOT(downloaded()) );

        connect(reply, SIGNAL(downloadProgress(qint64,qint64)),this, SLOT(progressSlot(qint64,qint64)) );
    }
}
