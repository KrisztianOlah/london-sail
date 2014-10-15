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

//Class to handle downloading maps for GUI
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
