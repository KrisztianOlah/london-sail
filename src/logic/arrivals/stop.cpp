#include "stop.h"

Stop::Stop(QObject* parent) : QObject(parent)
{
}

//public:

void Stop::setID(const QString& value) { id = value; }
void Stop::setLatitude(double value) { latitude = value; }
void Stop::setLongitude(double value) {longitude = value; }
void Stop::setName(const QString& value) { name = value;}
void Stop::setStopPointIndicator(const QString& value) { stopPointIndicator = value; }
void Stop::setTowards(const QString& value) { towards = value; }
void Stop::setType(int value) { type =value; }

void Stop::updated() { emit dataChanged(); }

//public slots:
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

QString Stop::getID() const { return id; }
double Stop::getLatitude() const { return latitude; }
double Stop::getLongitude() const { return longitude; }
QString Stop::getName() const { return name; }
QString Stop::getStopPointIndicator() const { return stopPointIndicator; }
QString Stop::getTowards() const { return towards; }
int Stop::getType() const { return type; }
