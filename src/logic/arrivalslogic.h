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
    QString currentDestination;
    Stop* currentStop;
    QString currentVehicleId;
    QString currentVehicleLine;
    QNetworkAccessManager* networkMngr;
    JourneyProgressContainer* journeyProgressContainer;
    QTimer* journeyProgressTimer;
    QNetworkReply* reply_arrivals;
    QNetworkReply* reply_busStop;
    QNetworkReply* reply_journeyProgress;
signals:
    void nextStopChanged();
    void stopDataChanged();
private:
    void clearCurrentStop();
    void clearArrivalsData();
    void clearJourneyProgressData();
    void getBusArrivalsByCode(const QString& code);
    void getBusProgress(const QString&);
    QList<QJsonDocument> makeDocument(QNetworkReply*);
private slots:
    void fetchArrivalsData();
    void fetchJourneyProgress();
    void onArrivalsDataReceived();
    void onBusProgressReceived();
    void onBusStopDataReceived();
    void onProgressDataChanged();
public slots:
    ArrivalsProxyModel* getArrivalsModel();
    void getBusStopByCode(const QString& code);
    void getBusStopsByName(const QString& name);
    QString getCurrentDestination() const;
    Stop* getCurrentStop();
    QString getCurrentVehicleLine() const;
    ArrivalsProxyModel* getJourneyProgressModel();
    QString getNextStop();
    void setCurrentDestination(const QString& destination);
    void setCurrentVehicleId(const QString& id);
    void setCurrentVehicleLine(const QString& line);
    void startArrivalsUpdate();
    void startJourneyProgressUpdate();
    void stopArrivalsUpdate();
    void stopJourneyProgressUpdate();
};

#endif // ARRIVALSLOGIC_H
