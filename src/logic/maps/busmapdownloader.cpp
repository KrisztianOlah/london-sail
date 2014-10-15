#include "busmapdownloader.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStandardPaths>

BusMapDownloader::BusMapDownloader(QObject* parent) : QObject(parent),
                                                      baseUrl("https://www.tfl.gov.uk/cdn/static/cms/documents/bus-route-maps/"),
                                                      downloading(false),
                                                      networkMngr(static_cast<QNetworkAccessManager*>(parent)),
                                                      reply(0),
                                                      running(false)
{
    connect(this, SIGNAL(itemAdded()), this, SLOT(onItemAdded()) );
    connect(this, SIGNAL(itemFinished()), this, SLOT(onItemFinished()) );
}

//public:
//returns true if download is in progress
bool BusMapDownloader::isDownloading() const { return downloading; }

//adds a new map to the download queue
void BusMapDownloader::queueMap(const BusMap& map) {
    queue.enqueue(map);
    emit itemAdded();
}

//adds a new map to the download queue overloaded
void BusMapDownloader::queueMap(const QString& name, const QString& link) {
    queue.enqueue(BusMap(name,link));
    emit itemAdded();
}

//private:
//Downloads a single map from the queue
void BusMapDownloader::downloadMap(const BusMap& map) {
    QString url = baseUrl + map.link;
    currentMap = map;
    qDebug() << "downloading " << map.name;

    reply = networkMngr->get(QNetworkRequest(QUrl(url)));
    connect(reply, SIGNAL(finished()), this, SLOT(onMapDownloaded()) );
}

//Starts downloading BusMaps in the queue
void BusMapDownloader::startQueue() {
    if (!queue.isEmpty()) {
        downloading = true;
        emit downloadingChanged();
        downloadMap(queue.dequeue());
    }
    else {
        downloading = false;
        emit downloadingChanged();
        running = false;
    }
}


//private slots:
//called when a new item is queued
void BusMapDownloader::onItemAdded() {
    if (!running) {
        running = true;
        startQueue();
    }
}

//called when an item in the queue is finished
void BusMapDownloader::onItemFinished() {
    startQueue();
}

//called when a file is downloaded, it saves the file on the disk if possible
void BusMapDownloader::onMapDownloaded() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QString("/busmaps");
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(path);
    }
    path = path + QString("/") + currentMap.name + QString(".pdf");
    qDebug() << "saving " << path;
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Couldn't open file for writing.";
    }
    else {
        file.write(reply->readAll());
        file.close();
    }
    reply->deleteLater();
    emit itemFinished();
}

