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
