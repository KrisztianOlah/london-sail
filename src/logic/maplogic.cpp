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

//can contain special html chars
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
    return name;
}

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
void MapLogic::onDownloadingChanged() {
    downloading = mapDownloader->isDownloading();
    emit downloadingChanged();
    qDebug() << "downloading changed to: " << downloading;
}

void MapLogic::onListOfMapsDownloaded() {
    QString page = reply->readAll();
    reply->deleteLater();
    parseListOfMapsPage(page);
}

void MapLogic::onMapDownloadFinished() {
    emit mapDownloaded();
}


//public slots:
void MapLogic::clearMapList() {
    mapsModel->clearData();
}

void MapLogic::deleteMap(const QString& name) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    path = path + QString("/busmaps/") + name + QString(".pdf");
    QFile file(path);
    bool ok = file.remove();
    //TODO Refresh model when item removed
    if (ok) {
        emit mapDeleted();
        qDebug() << name << "is removed successfuly.";
    }
    else qDebug() << "Removing" << name << "failed.";
}

void MapLogic::downloadListOfMapsFor(const QString& userInput) {
    //the full string for Kingston returns an empty list
    QString input = (userInput == "Kingston upon Thames") ? "Kingston" : userInput;
    QString request = baseUrl + input;
    QUrl url(request);
    reply = networkMngr->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()),this, SLOT(onListOfMapsDownloaded()) );
}

void MapLogic::downloadMap(const QString& name, const QString& link) {
    mapDownloader->queueMap(name,link);
}

bool MapLogic::isDownloading() const { return downloading; }

bool MapLogic::isThereLocalFile(const QString& name) const {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    path = path + QString("/busmaps/") + name + QString(".pdf");
    QFile file(path);
    return file.exists();
}

MapFilesModel* MapLogic::getMapFilesModel() { return mapFilesModel; }

MapsModel* MapLogic::getMapsModel() { return mapsModel; }


void MapLogic::openMap(const QString& name) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    path = QString("file:///") + path + QString("/busmaps/") + name + QString(".pdf");
    QUrl url(path);
    QDesktopServices::openUrl(url);
}
