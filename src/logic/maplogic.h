#ifndef MAPLOGIC_H
#define MAPLOGIC_H

#include <QList>
#include <QObject>
#include "maps/busmap.h"

class BusMapDownloader;
class MapFilesModel;
class MapsModel;
class QNetworkAccessManager;
class QNetworkReply;

class MapLogic : public QObject
{
    Q_OBJECT
public:
    explicit MapLogic(QObject *parent = 0);
private:
    QString baseUrl;
    bool downloading;
    QNetworkAccessManager* networkMngr;
    BusMapDownloader* mapDownloader;
    QList<BusMap> mapList;
    MapFilesModel* mapFilesModel;
    MapsModel* mapsModel;
    QNetworkReply* reply;

private:
    QString parseForLink(const QString&, int&);
    QString parseForName(const QString&, int&);
    void parseListOfMapsPage(const QString&);
signals:
    void downloadingChanged();
    void mapDownloaded();
    void mapDeleted();
private slots:
    void onDownloadingChanged();
    void onListOfMapsDownloaded();
    void onMapDownloadFinished();
public slots:
    void clearMapList();
    void deleteMap(const QString& name);
    void downloadListOfMapsFor(const QString&);
    void downloadMap(const QString& name, const QString& link);
    MapFilesModel* getMapFilesModel();
    MapsModel* getMapsModel();
    bool isDownloading() const;
    bool isThereLocalFile(const QString& name) const;
    void openMap(const QString& name);
};
#endif // MAPLOGIC_H
