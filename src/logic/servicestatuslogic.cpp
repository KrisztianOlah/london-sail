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

#include "servicestatuslogic.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QVariant>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include "serviceStatus/servicestatusxmlhandler.h"
#include "serviceStatus/thisweekendlinemodel.h"
#include "serviceStatus/servicestatusproxymodel.h"


//BUG When the internet connection fails after the first call to ServiceStatusLogic::refresh()
//all further calls to ServiceStatusLogic::refresh() will cause ServiceStatusLogic::downloaded()
//not to be called and Gui will show BusyIndicator without actually doing anything
//TODO function try block
ServiceStatusLogic::ServiceStatusLogic(QObject *parent) :
    QObject(parent),
    downloading(false),
    model(new ServiceStatusModel(this)),
    networkMngr(static_cast<QNetworkAccessManager*>(parent)),
    proxyModel(new ServiceStatusProxyModel(this)),
    url("http://cloud.tfl.gov.uk/TrackerNet/LineStatus") // /IncidentsOnly //add this later to improve network usage
{
    proxyModel->setSourceModel(model);
    proxyModel->sort(0);
}

// This function is supposed to parse the given QByteArray and return a QMap where key is the line and value is its status,
//if for some reason parsing failes the container will have its default state, see in constructor.
//TODO Error message for user if things go wrong
void ServiceStatusLogic::parse(const QByteArray& data) {
    QXmlSimpleReader xmlReader;
    QScopedPointer<QXmlInputSource> source(new QXmlInputSource());
    source.data()->setData(data);
    QScopedPointer<ServiceStatusXmlHandler> handler(new ServiceStatusXmlHandler(model));
    xmlReader.setContentHandler(handler.data());
    xmlReader.setErrorHandler(handler.data());

    bool ok = false;
    ok = xmlReader.parse(source.data());
    if (!ok) {
        qDebug() << ">>> Parsing failed <<<";
    }
    else {
        qDebug() << ">>> Parsed Successfuly <<<";
        emit dataChanged();
    }
    downloading = false;
    emit stateChanged();
}

//private slots:

//It will be called as soon as "reply" signals "finished()"
void ServiceStatusLogic::downloaded() {
    QByteArray data = reply->readAll();
    parse(data);
    reply->deleteLater();
}

//public slots:
ServiceStatusProxyModel* ServiceStatusLogic::getModel() { return proxyModel; }

//gives GUI an indication if download is in progress
bool ServiceStatusLogic::isDownloading() { return downloading; }

//GUI will call this slot to ask for data
void ServiceStatusLogic::refresh() {
    downloading = true;
    emit stateChanged();
    if (networkMngr) {
        if (model) { model->reset(); }
        reply = networkMngr->get(QNetworkRequest(url));
    }
    connect(reply, SIGNAL(finished()), this, SLOT(downloaded()) );
}
