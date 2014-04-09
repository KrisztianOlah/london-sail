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


#ifndef SERVICESTATUSLOGIC_H
#define SERVICESTATUSLOGIC_H

#include <QByteArray>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QUrl>
#include <QVariant>

class QNetworkAccessManager;
class QNetworkReply;
class QString;
class QXmlSimpleReader;

//ServiceStatusLogic is responsible for fetching, parsing the data required to display Service Status information
//it is also responsible of notifying ServiceStatusPage.qml when the data is ready to be displayed

// !!! parent MUST be a NetworkAccessManager or a nullptr !!!
class ServiceStatusLogic : public QObject
{
    Q_OBJECT
public:
    explicit ServiceStatusLogic(QObject *parent = 0);
    typedef QMap<QString,QPair<QString,QString> > Container;
signals:
    void dataChanged();
    void finished();
    void parsed();
    void stateChanged();
private:
    QScopedPointer<Container> container;
    bool downloading;
    QNetworkAccessManager* networkMngr;//handle for global obj
    QNetworkReply* reply;//handled by this class
    QUrl url;
private:
    QByteArray getData();
    void parse(const QByteArray&);
private slots:
    void downloaded();
public slots:
    QString getInfo(const QString&);
    QString getDetails(const QString&);
    bool isDownloading();
    void refresh();
};

#endif // SERVICESTATUSLOGIC_H
