#include "trafficxmlhandler.h"

#include <QDebug>
#include "trafficcontainer.h"

TrafficXmlHandler::TrafficXmlHandler(TrafficContainer* c) : container(c),
                                                            currentID(0),
                                                            inDisruption(false),
                                                            inPoint(false),
                                                            inStreet(false)
{
}

bool TrafficXmlHandler::characters(const QString& str) {
    currentText += str;
    return true;
}

bool TrafficXmlHandler::endElement(const QString& /*namespaceURI*/,const QString& /*localName*/,const QString& qName) {
    if (qName == "Disruption") {
        currentDisruption.id = currentID;
        currentID = 0;
        container->addDisruption(currentDisruption);
        inDisruption = false;
    }
    else if (qName == "Street") {
        container->addStreet(currentID, currentStreet);
        inStreet = false;
    }
    else if (qName == "Point") {
        inPoint = false;
    }
    //replace ',' with ", " if not followed by a whitespace, happends many times due to lousy typing
    //it is to make WordWrap possible in gui

    else if (inDisruption && qName == "location") {
        int i;
        while ((i = currentText.indexOf(QRegExp(",[^\\s-]"))) != -1 ) {
            currentText = currentText.insert(++i, " ");
        }
        currentDisruption.location = currentText;
    }
    else if (inDisruption && qName == "status") { currentDisruption.status = currentText; }
    else if (inDisruption && qName == "comments") { currentDisruption.comments = currentText; }
    else if (inDisruption && qName == "currentUpdate") { currentDisruption.currentUpdate = currentText; }
    else if (inDisruption && qName == "severity") { currentDisruption.severity = currentText; }
    else if (inDisruption && qName == "levelOfInterest") { currentDisruption.levelOfInterest = currentText; }
    else if (inDisruption && qName == "category") { currentDisruption.category = currentText; }
    else if (inDisruption && qName == "subCategory") { currentDisruption.subCategory = currentText; }
    else if (inDisruption && qName == "startTime") { currentDisruption.startTime = currentText; }
    else if (inDisruption && qName == "endTime") { currentDisruption.endTime = currentText; }
    else if (inDisruption && qName == "remarkTime") { currentDisruption.remarkTime = currentText; }
    else if (inDisruption && qName == "lastModTime") { currentDisruption.lastModTime = currentText; }
    else if (inDisruption && inPoint && qName == "coordinatesLL") { currentDisruption.coordinates = currentText; }
    else if (inDisruption && inStreet && qName == "name") {
        int i;
        while ((i = currentText.indexOf(QRegExp(",[^\\s-]"))) != -1 ) {
            currentText = currentText.insert(++i, " ");
        }
        currentStreet.name = currentText;
    }
    else if (inDisruption && inStreet && qName == "closure") {
        currentStreet.closure = (currentText == "Open") ? "Affected" : currentText;
    }
    else if (inDisruption && inStreet && qName == "directions") {currentStreet.directions = currentText.toLower(); }
    return true;
}

bool TrafficXmlHandler::startElement(const QString& /*namespaceURI*/,const QString& /*localName*/,
                          const QString& qName,const QXmlAttributes& atts) {
    if (qName == "Disruption") {
        inDisruption = true;
        currentID = atts.value("id").toInt();
    }
    else if (qName == "Street") {
        inStreet = true;
    }
    else if (qName == "Point") {
        inPoint = true;
    }
    else if (qName == "status" || qName == "severity" || qName == "levelOfInterest" || qName == "category" ||
             qName == "subCategory" || qName == "startTime" || qName == "location" || qName == "comments" ||
             qName == "currentUpdate" || qName == "coordinatesLL" || qName == "name" || qName == "closure" ||
             qName == "directions" || qName == "endTime" || qName == "remarkTime" || qName == "lastModTime") {

        currentText = "";
    }
    return true;
}
//refresh time: 5 min
//display time: max 30 min
