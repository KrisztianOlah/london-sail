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

#include "stop.h"
#include <QDebug>
#include "../database/databasemanager.h"

// !!! see header for note about parent !!!
Stop::Stop(QObject* parent) : QObject(parent),
                              databaseManager(static_cast<DatabaseManager*>(parent))
{
}

//public:
//setters
void Stop::setID(const QString& value) { id = value; }
void Stop::setLatitude(double value) { latitude = value; }
void Stop::setLongitude(double value) { longitude = value; }
void Stop::setName(const QString& value) { name = value;}
void Stop::setStopPointIndicator(const QString& value) { stopPointIndicator = value; }
void Stop::setTowards(const QString& value) { towards = value; }
void Stop::setType(int value) { type =value; }

void Stop::updated() { emit dataChanged(); }

//public slots:
//adds itself to the database
void Stop::addToDb(bool favorite) {
    if (databaseManager) {
        databaseManager->addStop(name, id, type, towards, latitude, longitude,stopPointIndicator, favorite);
    }
}

//resets itself to a sensible default value
void Stop::clear() {
    type = None;
    id = "";
    latitude = 0;
    longitude = 0;
    name = "";
    stopPointIndicator = "";
    towards = "";

    emit dataChanged();
}

//getters
QString Stop::getID() const { return id; }
double Stop::getLatitude() const { return latitude; }
double Stop::getLongitude() const { return longitude; }
QString Stop::getName() const { return name; }
QString Stop::getStopPointIndicator() const { return stopPointIndicator; }
QString Stop::getTowards() const { return towards; }
int Stop::getType() const { return type; }
