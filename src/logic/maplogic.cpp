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

#include "maplogic.h"

#include <QDebug>
#include <QDesktopServices>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegExp>
#include <QStandardPaths>
#include <QStringList>
#include "maps/busmapdownloader.h"
#include "maps/mapfilesmodel.h"
#include "maps/mapsmodel.h"



//https://www.tfl.gov.uk/cdn/static/cms/documents/bus-route-maps/
MapLogic::MapLogic(QObject *parent) : QObject(parent),
                                      baseUrl("https://www.tfl.gov.uk/maps_/bus-route-maps?Query="),
                                      downloading(false),
                                      networkMngr(static_cast<QNetworkAccessManager*>(parent)),
                                      mapDownloader(new BusMapDownloader(networkMngr)),
                                      mapFilesModel(new MapFilesModel(this)),
                                      mapsModel(new MapsModel(&mapList,this)),
                                      reply(0)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QString("/busmaps");
    mapFilesModel->setRootPath(path);

    connect(mapDownloader, SIGNAL(itemFinished()), this, SLOT(onMapDownloadFinished()) );
    connect(mapDownloader, SIGNAL(downloadingChanged()), this, SLOT(onDownloadingChanged())  );
}
//private:
//Parses webpage for downloadable map files
QString MapLogic::parseForLink(const QString& page, int& pos) {
    QRegExp re("document-download-wrap  pdf. href=.");
    QRegExp reEnd("\"");
    QString link;
    int beginPos = re.indexIn(page,pos) + 35;//num of chars in re
    //if no match
    if (beginPos != 34) {
        int endPos = reEnd.indexIn(page,beginPos);
        for (int i = beginPos;i != endPos;++i) {
            link += page.at(i);
        }
        pos = endPos;
    }
    else pos = -1;
    //only need the last part, the rest is constant
    QStringList list = link.split('/');
    if (list.size() > 0) {
        link = list.at(list.size() -1);
    }
    return link;
}

//Parses webpage for map names that can be displayed to user, can contain special html chars
QString MapLogic::parseForName(const QString& page, int& pos) {
    QRegExp re("document-download-text\"><p>");
    QRegExp reEnd("</p></div>");
    QString name;
    int beginPos = re.indexIn(page,pos) + 27;//num of chars in re
    //if no match
    if (beginPos != 26) {
        int endPos = reEnd.indexIn(page,beginPos);
        for (int i = beginPos; i != endPos; ++i) {
            name += page.at(i);
        }
        pos = endPos;
    }
    else pos = -1;
    //trim any heading or trailing whitespace
    return name.trimmed();
}

//Parses the webpage, delegates the real work to parseForLink(args) and parseForName(args)
void MapLogic::parseListOfMapsPage(const QString& page) {
    int pos = 0;
    while (pos != -1) {
        BusMap map;
        map.link = parseForLink(page,pos);
        map.name = parseForName(page,pos);
        if (map.name != "") {
            mapsModel->addMap(map);
        }
    }
}

//private slots:
//Called when mapDownloader's downloading state is changed
void MapLogic::onDownloadingChanged() {
    downloading = mapDownloader->isDownloading();
    emit downloadingChanged();
}

//Called when downloadListOfMapsFor(arg) finished and reply is ready to process
void MapLogic::onListOfMapsDownloaded() {
    downloading = false;
    emit downloadingChanged();
    QString page = reply->readAll();
    reply->deleteLater();
    parseListOfMapsPage(page);
}

//Called when a single map in the queue is downloaded
void MapLogic::onMapDownloadFinished() {
    emit mapDownloaded();
}


//public slots:
//Clears map model so that wnen new model is requested, wrong data will not be presented to user
void MapLogic::clearMapList() {
    mapsModel->clearData();
}

//Deletes a map by name, called from GUI
void MapLogic::deleteMap(const QString& name) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    path = path + QString("/busmaps/") + name + QString(".pdf");
    QFile file(path);
    bool ok = file.remove();
    if (ok) {
        emit mapDeleted();
        qDebug() << name << "is removed successfuly.";
    }
    else qDebug() << "Removing" << name << "failed.";
}

//Downloads a list of maps for a given area or route
void MapLogic::downloadListOfMapsFor(const QString& userInput) {
    //the full string for Kingston returns an empty list
    QString input = (userInput == "Kingston upon Thames") ? "Kingston" : userInput;
    QString request = baseUrl + input;
    QUrl url(request);
    downloading = true;
    emit downloadingChanged();
    reply = networkMngr->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()),this, SLOT(onListOfMapsDownloaded()) );
}

//Adds a map to the download queue called by GUI
void MapLogic::downloadMap(const QString& name, const QString& link) {
    mapDownloader->queueMap(name,link);
}

//returns true if mapDownloader or MapLogic is downloading otherwise false, called from GUI
bool MapLogic::isDownloading() const { return downloading; }

//Returns true if file with name exists in a map data location, called from GUI
bool MapLogic::isThereLocalFile(const QString& name) const {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    path = path + QString("/busmaps/") + name + QString(".pdf");
    QFile file(path);
    return file.exists();
}

//Used by MyMapsPage
MapFilesModel* MapLogic::getMapFilesModel() { return mapFilesModel; }

//Used by BusMapsPage
MapsModel* MapLogic::getMapsModel() { return mapsModel; }

//Opens a map file externally with default pdf viewer
void MapLogic::openMap(const QString& name) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    path = QString("file:///") + path + QString("/busmaps/") + name + QString(".pdf");
    QUrl url(path);
    QDesktopServices::openUrl(url);
}
