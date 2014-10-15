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
