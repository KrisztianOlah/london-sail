#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

struct Vehicle
{
    enum Type { Boat, Bus, Dlr, OverGround, UnderGround };
    Vehicle();
    QString id;//for bus it's the registration number
    QString line;
    QString destination;
    int eta; //in minutes
    QString towards;
    QString platform;
    int type;
};

#endif // VEHICLE_H
