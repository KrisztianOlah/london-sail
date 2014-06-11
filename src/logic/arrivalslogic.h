#ifndef ARRIVALSLOGIC_H
#define ARRIVALSLOGIC_H

#include <QHash>
#include <QObject>
#include <QString>

class ArrivalsContainer;
class ArrivalsModel;
class ArrivalsProxyModel;
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
    Stop* currentStop;
    QNetworkAccessManager* networkMngr;
    QNetworkReply* reply_arrivals;
    QNetworkReply* reply_busStop;
signals:
    void stopDataChanged();
private:
    void getBusArrivalsByCode(const QString& code);
    QList<QJsonDocument> makeDocument(QNetworkReply*);
private slots:
    void fetchArrivalsData();
    void onArrivalsDataReceived();
    void onBusStopDataReceived();
public slots:
    void clearCurrentStop();
    ArrivalsProxyModel* getArrivalsModel();
    void getBusStopByCode(const QString& code);
    void getBusStopsByName(const QString& name);
    Stop* getCurrentStop();
    void startArrivalsUpdate();
    void stopArrivalsUpdate();
};

#endif // ARRIVALSLOGIC_H
