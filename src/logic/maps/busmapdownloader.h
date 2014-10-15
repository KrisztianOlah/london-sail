#ifndef BUSMAPDOWNLOADER_H
#define BUSMAPDOWNLOADER_H

#include <QObject>
#include <QQueue>
#include "busmap.h"

class QNetworkAccessManager;
class QNetworkReply;

//Class to queue and download BusMap objects
class BusMapDownloader : public QObject
{
    Q_OBJECT
public:
    explicit BusMapDownloader(QObject* parent = 0);
private:
    QString baseUrl;
    bool downloading;
    BusMap currentMap;
    QNetworkAccessManager* networkMngr;
    QQueue<BusMap> queue;
    QNetworkReply* reply;
    bool running;//queue
public:
    bool isDownloading() const;
    void queueMap(const BusMap&);
    void queueMap(const QString& name, const QString& link);
private:
    void downloadMap(const BusMap&);
    void startQueue();
signals:
    void downloadingChanged();
    void itemAdded();
    void itemFinished();//emitted when item is written to file
    void itemDownloaded();
    void queueFinished();
private slots:
    void onItemAdded();
    void onItemFinished();
    void onMapDownloaded();
public slots:

};

#endif // BUSMAPDOWNLOADER_H
