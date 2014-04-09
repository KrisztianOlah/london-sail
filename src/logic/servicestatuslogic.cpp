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
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QVariant>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include "servicestatusxmlhandler.h"


//BUG When the internet connection fails after the first call to ServiceStatusLogic::refresh()
//all further calls to ServiceStatusLogic::refresh() will cause ServiceStatusLogic::downloaded()
//not to be called and Gui will show BusyIndicator without actually doing anything

ServiceStatusLogic::ServiceStatusLogic(QObject *parent) :
    QObject(parent),
    container(new QMap<QString,QPair<QString,QString> >() ),
    downloading(false),
    networkMngr(static_cast<QNetworkAccessManager*>(parent)),
    url("http://cloud.tfl.gov.uk/TrackerNet/LineStatus") // /IncidentsOnly //add this later to improve network usage
{
    //Giving some sensible initial values for container
    container->insert("Bakerloo",{"",""});
    container->insert("Central",{"",""});
    container->insert("Circle",{"",""});
    container->insert("DLR",{"",""});
    container->insert("District",{"",""});
    container->insert("Hammersmith and City",{"",""});
    container->insert("Jubilee",{"",""});
    container->insert("Metropolitan",{"",""});
    container->insert("Northern",{"",""});
    container->insert("Overground",{"",""});
    container->insert("Piccadilly",{"",""});
    container->insert("Victoria",{"",""});
    container->insert("Waterloo and City",{"",""});


}

// This function is supposed to parse the given QByteArray and return a QMap where key is the line and value is its status,
//if for some reason parsing failes the container will have its default state, see in constructor.
//TODO Error message for user if things go wrong
void ServiceStatusLogic::parse(const QByteArray& data) {
    //FIX delete xmlReader and source
    xmlReader = new QXmlSimpleReader();
    QXmlInputSource* source = new QXmlInputSource();
    source->setData(data);
    ServiceStatusXmlHandler* handler = new ServiceStatusXmlHandler(container);
    xmlReader->setContentHandler(handler);
    xmlReader->setErrorHandler(handler);

    bool ok = false;
    ok = xmlReader->parse(source);
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
    parse(reply->readAll());
    reply->deleteLater();
}

//public slots:

//GUI will ask for this data when "stateChanged()" is emitted by *this
QString ServiceStatusLogic::getInfo(const QString& str) {
    QString ret = (*container)[str].first;
    return ret;
}

//GUI will ask for this data when "stateChanged()" is emitted by *this
QString ServiceStatusLogic::getDetails(const QString& str) {
    QString ret = (*container)[str].second;
    return ret;
}

//gives GUI an indication if download is in progress
bool ServiceStatusLogic::isDownloading() { return downloading; }

//GUI will call this slot to ask for data
void ServiceStatusLogic::refresh() {
    downloading = true;
    emit stateChanged();
    //FIX if nullptr
    reply = networkMngr->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()), this, SLOT(downloaded()) );
}
