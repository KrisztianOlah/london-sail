#ifndef TRAFFICLOGIC_H
#define TRAFFICLOGIC_H

#include <QObject>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;
class TrafficContainer;
class DisruptionProxyModel;
class StreetModel;

// !!! Parent MUST be a QNetworkAccessManager or a nullptr !!!
class TrafficLogic : public QObject
{
    Q_OBJECT
public:
    explicit TrafficLogic(QObject *parent = 0);
private:
    TrafficContainer* container;
    bool downloading;
    QNetworkAccessManager* networkMngr;
    bool parsing;
    QNetworkReply* reply;
    QUrl url;
private:
    void parseData(const QByteArray&);
signals:
    void downloadProgress(qint64 value);
    void stateChanged();
private slots:
    void downloaded();
    void progressSlot(qint64,qint64);
public slots:
    DisruptionProxyModel* getDisruptionModel();
    StreetModel* getStreetModel(int id);
    bool isDownloading();
    bool isParsing();
    void refresh();
};

#endif // TRAFFICLOGIC_H
