#ifndef TRAFFICXMLREADER_H
#define TRAFFICXMLREADER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QSharedPointer>
#include "disruption.h"
#include "street.h"
#include "trafficcontainer.h"


class TrafficXmlReader : public QObject
{
    Q_OBJECT
public:
    TrafficXmlReader(QObject* parent = 0);
private:
    TrafficContainer* container;
    int currentID;
    Disruption currentDisruption;
    Street currentStreet;
    bool inDisruption;
    bool inPoint;
    bool inStreet;
    QXmlStreamReader reader;
public:
    void setContainer(TrafficContainer*);
    void setDevice(QIODevice*);
signals:
    void finished();
    void partFinished();
public slots:
    void addData(const QByteArray&);
    void parse();
    void parseAvailableData(const QByteArray&);
};

#endif // TRAFFICXMLREADER_H
