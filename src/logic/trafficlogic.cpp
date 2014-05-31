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

#include "trafficlogic.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>

#include "traffic/disruptionproxymodel.h"
#include "traffic/trafficcontainer.h"
#include "traffic/trafficxmlreader.h"

// !!! See header for note on parent !!!
TrafficLogic::TrafficLogic(QObject *parent) :
    QObject(parent),
    container(new TrafficContainer(this)),
    downloading(false),
    networkMngr(static_cast<QNetworkAccessManager*>(parent)),
    parsing(false),
    workContainer(0),
    reader(0),
    reply(0),
    url("http://data.tfl.gov.uk/tfl/syndication/feeds/tims_feed.xml?app_id=663a8a04&app_key=a1f29a8c881ffd777431a7cecf6c2d3b")
{
}

//private:

//private slots:
void TrafficLogic::onAllDataRecieved() {
    downloading = false;
    emit stateChanged();
    reply->deleteLater();
}

void TrafficLogic::onDataRecieved() {
    parsing = true;
    emit stateChanged();
    emit dataReady(reply->readAll());
}

void TrafficLogic::onParsingFinished() {
    parsing = false;
    emit stateChanged();
    if (container && workContainer) {
        container->swap(*workContainer);
        delete workContainer;
        workContainer = 0;
    }
    else {
        if (!container) qDebug() << "container is nullptr";
        if (!workContainer) qDebug() << "workContainer is nullptr";
    }
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
    if (networkMngr && !parsing) {
        workContainer = new TrafficContainer(this);
        reader = new TrafficXmlReader(workContainer);
        QThread* parserThread = new QThread(/*reader*/);
        reader->moveToThread(parserThread);

        connect(reader, SIGNAL(finished()), this, SLOT(onParsingFinished()) );
        connect(reader, SIGNAL(finished()), parserThread, SLOT(quit()) );

        connect(reader, SIGNAL(finished()), reader, SLOT(deleteLater()) );
        connect(parserThread, SIGNAL(finished()), parserThread, SLOT(deleteLater()) );

        parserThread->start();

        reply = networkMngr->get(QNetworkRequest(url));
        downloading = true;
        emit stateChanged();

        connect(reply, SIGNAL(finished()), this, SLOT(onAllDataRecieved()) );
        connect(reply, SIGNAL(downloadProgress(qint64,qint64)),this, SLOT(progressSlot(qint64,qint64)) );
        connect(reply, SIGNAL(readyRead()), this, SLOT(onDataRecieved()) );
        connect(this, SIGNAL(dataReady(QByteArray)), reader, SLOT(parseAvailableData(QByteArray)) );
    }
}
