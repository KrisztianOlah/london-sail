#ifndef STOP_H
#define STOP_H

#include <QString>
#include <QObject>

//StopPointName,StopPointIndicator,Towards,Latitude,Longitude
class Stop : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)

public:
    explicit Stop(QObject*  parent = 0);
    enum Type { None, Bus, Underground, River, Overground, Dlr};
private:
    QString id;
    double latitude;//will be replaced with QCoordinates
    double longitude;//   -||-
    QString name;
    QString stopPointIndicator;//for bus stops
    QString towards;//might be empty string for some type such as tube
    int type;
public:
    void setID(const QString&);
    void setLatitude(double);
    void setLongitude(double);
    void setName(const QString&);
    void setStopPointIndicator(const QString&);
    void setTowards(const QString&);
    void setType(int);
    void updated();
signals:
    void dataChanged();
public slots:
    void clear();
    QString getID() const;
    double getLatitude() const;
    double getLongitude() const;
    QString getName() const;
    QString getStopPointIndicator() const;
    QString getTowards() const;
    int getType() const;
};

#endif // STOP_H
//wget -O instant http://countdown.api.tfl.gov.uk/interfaces/ura/instant_V1?StopPointName="Greyhound Road"\&ReturnList=StopCode1,StopPointName,Bearing,StopPointIndicator,StopPointType,Latitude,Longitude
