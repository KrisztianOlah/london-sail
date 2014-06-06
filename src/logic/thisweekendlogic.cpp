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

#include "thisweekendlogic.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlSimpleReader>

#include "serviceStatus/servicestatusproxymodel.h"
#include "serviceStatus/thisweekendxmlhandler.h"
#include "serviceStatus/thisweekendlinemodel.h"

ThisWeekendLogic::ThisWeekendLogic(QObject *parent) :
    QObject(parent),
    downloading(false),
    model(new ThisWeekendLineModel(this)),
    networkMngr(static_cast<QNetworkAccessManager*>(parent)),
    proxyModel(new ServiceStatusProxyModel(this)),
    url("http://www.tfl.gov.uk/tfl/businessandpartners/syndication/feed.aspx?email=fasza2mobile@gmail.com&feedId=7")
{
    proxyModel->setSourceModel(model);
    proxyModel->sort(0);
}

//private:
//parses data and populates model
void ThisWeekendLogic::parseData(const QByteArray& data) {
    QXmlSimpleReader xmlReader;
    QScopedPointer<QXmlInputSource> source(new QXmlInputSource());
    source.data()->setData(data);
    QScopedPointer<ThisWeekendXmlHandler> handler(new ThisWeekendXmlHandler(model));
    xmlReader.setContentHandler(handler.data());
    xmlReader.setErrorHandler(handler.data());
    bool ok = false;
    ok = xmlReader.parse(source.data());
    if (ok) {
        qDebug() << "Parsed Successfuly";
        emit dataParsed();
    }
    else {
        qDebug() << "Parsing failed";
    }
    qDebug() << "Not Downloading";
    downloading = false;
    emit stateChanged();
}

//private slots:
//This slot is called when data is downloaded
void ThisWeekendLogic::downloaded() {
    parseData(reply->readAll());
    reply->deleteLater();
}

//public slots:
//returns a model handle to GUI
ServiceStatusProxyModel* ThisWeekendLogic::getModel() { return proxyModel; }

//to indicate if download is in progress
bool ThisWeekendLogic::isDownloading() { return downloading; }

//This slot called from GUI to get data displayed
//TODO log nullptr
void ThisWeekendLogic::refresh() {
    if (networkMngr) {
        if (model) { model->reset(); }
        downloading = true;
        emit stateChanged();
        reply = networkMngr->get(QNetworkRequest(url));//will be deleted later
        connect(reply, SIGNAL(finished()), this, SLOT(downloaded()) );
    }
}

