#ifndef ARRIVALSLOGIC_H
#define ARRIVALSLOGIC_H

#include <QHash>
#include <QObject>
#include <QString>

class ArrivalsContainer;
class ArrivalsModel;
class ArrivalsProxyModel;
class JourneyProgressContainer;
class QNetworkAccessManager;
class QNetworkReply;
class QTimer;
class Stop;

class ArrivalsLogic : public QObject
{
    Q_OBJECT
public:
    explicit ArrivalsLogic(QObject *parent = 0);
private:
    QString activeStops;
    ArrivalsContainer* arrivalsContainer;
    ArrivalsModel* arrivalsModel;
    ArrivalsProxyModel* arrivalsProxyModel;
    QTimer* arrivalsTimer;
    QString baseUrl;
    QString currentBusDirectionId;
    Stop* currentStop;
    QString currentVehicleId;
    QNetworkAccessManager* networkMngr;
    JourneyProgressContainer* journeyProgressContainer;
    QTimer* journeyProgressTimer;
    QNetworkReply* reply_arrivals;
    QNetworkReply* reply_busStop;
    QNetworkReply* reply_journeyProgress;
signals:
    void stopDataChanged();
private:
    void getBusArrivalsByCode(const QString& code);
    void getBusProgress(const QString&);
    QList<QJsonDocument> makeDocument(QNetworkReply*);
private slots:
    void fetchArrivalsData();
    void fetchJourneyProgress();
    void onArrivalsDataReceived();
    void onBusProgressReceived();
    void onBusStopDataReceived();
public slots:
    void clearArrivalsData();
    void clearJourneyProgressData();
    void clearCurrentStop();
    ArrivalsProxyModel* getArrivalsModel();
    ArrivalsProxyModel* getJourneyProgressModel();
    void getBusStopByCode(const QString& code);
    void getBusStopsByName(const QString& name);
    Stop* getCurrentStop();
    void setCurrentVehicleId(const QString& id);
    void startArrivalsUpdate();
    void startJourneyProgressUpdate();
    void stopArrivalsUpdate();
    void stopJourneyProgressUpdate();
};

#endif // ARRIVALSLOGIC_H
