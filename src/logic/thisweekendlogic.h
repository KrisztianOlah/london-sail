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

#ifndef THISWEEKENDLOGIC_H
#define THISWEEKENDLOGIC_H

#include <QByteArray>
#include <QObject>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;
class ThisWeekendLineModel;

// !!! parent must be a NetworkAccessManager or nullptr(default)
//This class is the logic behind "This Weekend/Weekend Disruption" feature
class ThisWeekendLogic : public QObject
{
    Q_OBJECT
public:
    explicit ThisWeekendLogic(QObject *parent = 0);
private:
    bool downloading;
    ThisWeekendLineModel* model;//Qt memory management
    QNetworkAccessManager* networkMngr;//just a handle for global QNetworkAccessManager
    QNetworkReply* reply;//handled in class
    QUrl url;
private:
    void parseData(const QByteArray&);
signals:
    void dataParsed();
    //to indicate change in downloading/parsing state
    void stateChanged();
private slots:
    void downloaded();
public slots:
    ThisWeekendLineModel* getModel();
    bool isDownloading();
    void refresh();
};

#endif // THISWEEKENDLOGIC_H
