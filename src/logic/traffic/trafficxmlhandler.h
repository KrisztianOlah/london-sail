#ifndef TRAFFICXMLHANDLER_H
#define TRAFFICXMLHANDLER_H

#include <QString>
#include <QXmlDefaultHandler>

#include "disruption.h"
#include "street.h"

class TrafficContainer;

class TrafficXmlHandler : public QXmlDefaultHandler
{
public:
    explicit TrafficXmlHandler(TrafficContainer* = 0);
private:
    TrafficContainer* container;
    Disruption currentDisruption;
    int currentID;
    Street currentStreet;
    QString currentText;
    bool inDisruption;
    bool inPoint;
    bool inStreet;
public:
    virtual bool characters(const QString& str);
    virtual bool endElement(const QString& namespaceURI,const QString& localName,const QString& qName);
    virtual bool startElement(const QString& namespaceURI,const QString& localName,
                              const QString& qName,const QXmlAttributes& atts);

};

#endif // TRAFFICXMLHANDLER_H
