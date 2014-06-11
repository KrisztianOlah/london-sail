#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

struct Vehicle
{
    enum Type { Boat, Bus, Dlr, OverGround, UnderGround };
    Vehicle();
    QString id;
    QString line;
    QString destination;
    int eta; //minutes
    QString towards;
    QString platform;
    int type;
};

#endif // VEHICLE_H
