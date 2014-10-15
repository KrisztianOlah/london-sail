#ifndef BUSMAP_H
#define BUSMAP_H

#include <QString>

//Struct to hold a Bus Map object during parsing
struct BusMap
{
    BusMap();
    BusMap(const QString& name, const QString& link);
    QString name;
    QString link;
};

#endif // BUSMAP_H
