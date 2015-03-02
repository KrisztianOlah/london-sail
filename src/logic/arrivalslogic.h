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

#ifndef ARRIVALSLOGIC_H
#define ARRIVALSLOGIC_H

#include <QHash>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

class ArrivalsContainer;
class ArrivalsModel;
class ArrivalsProxyModel;
class DatabaseManager;
class JourneyProgressContainer;
class QNetworkAccessManager;
class QNetworkReply;
class QTimer;
class Stop;
class StopsQueryModel;
class QStringListModel;

//This class is reponsible to providing the logic to all departure related queries from gui
class ArrivalsLogic : public QObject
{
    Q_OBJECT
public:
    explicit ArrivalsLogic(DatabaseManager* = 0, QObject* parent = 0);
private:
    QString activeStops;
    ArrivalsContainer* arrivalsContainer;
    ArrivalsModel* arrivalsModel;
    ArrivalsProxyModel* arrivalsProxyModel;
    QTimer* arrivalsTimer;
    QString baseUrl;
    QString currentBusDirectionId;
    QString currentDestination;


    QString currentVehicleId;
    QString currentVehicleLine;
    DatabaseManager* databaseManager;
    Stop* currentStop;
    QString currentStopMessages;
    QTimer* displayTimer;
    bool downloadingArrivals;
    bool downloadingJourneyProgress;
    bool downloadingListOfStops;
    bool downloadingStop;
    QNetworkAccessManager* networkMngr;
    JourneyProgressContainer* journeyProgressContainer;
    QTimer* journeyProgressTimer;
    QNetworkReply* reply_arrivals;
    QNetworkReply* reply_busStop;
    QNetworkReply* reply_busStopMessage;
    QNetworkReply* reply_journeyProgress;
    QNetworkReply* reply_stations;
    QNetworkReply* reply_stops;
    StopsQueryModel* stopsQueryModel;
signals:
    void currentStopMessagesChanged();
    void downloadStateChanged();
    void nextStopChanged();
    void displayTimerTicked();
    void stopDataChanged();
private:
    void clearArrivalsData();
    void clearJourneyProgressData();
    void downloadStations();
    void fillCurrentStopMessages(const QMap<int,QString>&);
    void getBusArrivalsByCode(const QString& code);
    void getBusProgress(const QString&);
    QList<QJsonDocument> makeDocument(QNetworkReply*);
private slots:
    void fetchArrivalsData();
    void fetchJourneyProgress();
    void onArrivalsDataReceived();
    void onBusProgressReceived();
    void onBusStopDataReceived();
    void onBusStopMessageReceived();
    void onDisplayTimerTicked();
    void onListOfBusStopsReceived();
    void onProgressDataChanged();
    void onStationsDownloaded();
public slots:
    void clearCurrentStop();
    bool favorStop(const QString& code, bool);
    ArrivalsProxyModel* getArrivalsModel();
    void getBusStopByCode(const QString& code);
    void getBusStopMessage(const QString& code);
    void getBusStopsByName(const QString& name);
    QString getCurrentDestination() const;
    Stop* getCurrentStop();
    QString getCurrentStopMessages() const;
    QString getCurrentVehicleLine() const;
    double getTimerProgress_arrivals() const;
    double getTimerProgress_journeyProgress() const;
    bool isDownloadingArrivals() const;
    bool isDownloadingJourneyProgress() const;
    bool isDownloadingListOfStops() const;
    bool isDownloadingStop() const;
    ArrivalsProxyModel* getJourneyProgressModel();
    QString getNextStop();
    StopsQueryModel* getStopsQueryModel();
    bool isStopFavorite(const QString& code);
    void refreshArrivalsModel();
    void setCurrentDestination(const QString& destination);
    void setCurrentVehicleId(const QString& id);
    void setCurrentVehicleLine(const QString& line);
    void setStopsQueryModel(int type);
    void startArrivalsUpdate();
    void startJourneyProgressUpdate();
    void stopArrivalsUpdate();
    void stopJourneyProgressUpdate();
};

#endif // ARRIVALSLOGIC_H
