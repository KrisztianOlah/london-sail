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

#include "trafficxmlreader.h"

#include <QDebug>
#include <QRegExp>
#include "trafficcontainer.h"

TrafficXmlReader::TrafficXmlReader(QObject* c) : container(static_cast<TrafficContainer*>(c)),
                                                          currentID(0),
                                                          inDisruption(false),
                                                          inPoint(false),
                                                          inStreet(false)
{
    reader.setNamespaceProcessing(false);
}

//public slots:
//appends to QXmlStreamreader's data
void TrafficXmlReader::addData(const QByteArray& data) { reader.addData(data);  qDebug() << "+++++++";/*qDebug() << data; */}

//Function to parse data available, it will emit partFinished() if data is not yet
//complete, once it is complete finished() signal will be emitted
//TODO error handling
void TrafficXmlReader::parse() {
    if (!container) return;
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.qualifiedName() == "Disruption") {
            if (reader.isStartElement()) {
                inDisruption = true;
                currentID = reader.attributes().value("id").toInt();
            }
            else if (reader.isEndElement()) {
                currentDisruption.id = currentID;
                currentID = 0;
                container->addDisruption(currentDisruption);
                inDisruption = false;
            }
        }
        else if (inDisruption && reader.qualifiedName() == "status") {
            currentDisruption.status = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "severity") {
            currentDisruption.severity = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "levelOfInterest") {
            currentDisruption.levelOfInterest = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "category") {
            currentDisruption.category = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "subCategory") {
            currentDisruption.subCategory = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "startTime") {
            currentDisruption.startTime = reader.readElementText();
        }
        //replace ',' with ", " if not followed by a whitespace, happends many times due to lousy typing
        //it is to make WordWrap possible in gui
        else if (inDisruption && reader.qualifiedName() == "location") {
            QString location = reader.readElementText();
            if (location == "") qDebug() << "!!!!!!!!!!!";
            int i;
            while ((i = location.indexOf(QRegExp(",[^\\s-]"))) != -1 ) {
                location = location.insert(++i, " ");
            }
            currentDisruption.location = location;
//            if (location == "") qDebug() << "***this >>>>" << copy; //qDebug() << "!!!!!!!!!!!";
//            else qDebug() << location;
        }
        else if (inDisruption && reader.qualifiedName() == "comments") {
            currentDisruption.comments = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "currentUpdate") {
            currentDisruption.currentUpdate = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "remarkTime") {
            currentDisruption.remarkTime = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "lastModTime") {
            currentDisruption.lastModTime = reader.readElementText();
        }
        else if (inDisruption && reader.qualifiedName() == "Point") {
            inPoint = true;
        }
        else if (inDisruption && inPoint && reader.qualifiedName() == "coordinatesLL") {
            currentDisruption.coordinates = reader.readElementText();
        }

        //Streets
        else if (inDisruption && reader.qualifiedName() == "Street") {
            if (reader.isStartElement()) {
                inStreet = true;
            }
            else if (reader.isEndElement()) {
                container->addStreet(currentID, currentStreet);
            }
        }
        else if (inDisruption && inStreet && reader.qualifiedName() == "name") {
            QString name = reader.readElementText();
            int i;
            while ((i = name.indexOf(QRegExp(",[^\\s-]"))) != -1 ) {
                name = name.insert(++i, " ");
            }
            currentStreet.name = name;
        }
        else if (inDisruption && inStreet && reader.qualifiedName() == "closure") {
            QString closure = reader.readElementText();
                currentStreet.closure = (closure == "Open") ? "Affected" : closure;
        }
        else if (inDisruption && inStreet && reader.qualifiedName() == "directions") {
            currentStreet.directions = reader.readElementText().toLower();
        }

        if (reader.hasError()) {
            if (reader.error() == QXmlStreamReader::PrematureEndOfDocumentError) {
                emit partFinished();
            }
            else { qDebug() << "An Error has occured while parsing."; }
        }
    }
    if (!reader.hasError()) {
        emit finished();
    }
}

//a slot to be connected when running in a different thread due to how QThread works
void TrafficXmlReader::parseAvailableData(const QByteArray& data) {
    addData(data);
    parse();
}
