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
bool BusMapDownloader::isDownloading() const { return downloading; }

void BusMapDownloader::queueMap(const BusMap& map) {
    queue.enqueue(map);
    emit itemAdded();
}

void BusMapDownloader::queueMap(const QString& name, const QString& link) {
    queue.enqueue(BusMap(name,link));
    emit itemAdded();
}

//private:
void BusMapDownloader::downloadMap(const BusMap& map) {
    QString url = baseUrl + map.link;
    currentMap = map;
    qDebug() << "downloading " << map.name;

    reply = networkMngr->get(QNetworkRequest(QUrl(url)));
    connect(reply, SIGNAL(finished()), this, SLOT(onMapDownloaded()) );
}

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
void BusMapDownloader::onItemAdded() {
    if (!running) {
        running = true;
        startQueue();
    }
}

void BusMapDownloader::onItemFinished() {
    startQueue();
}

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

