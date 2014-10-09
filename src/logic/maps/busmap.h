#ifndef BUSMAP_H
#define BUSMAP_H

#include <QString>

struct BusMap
{
    BusMap();
    BusMap(const QString& name, const QString& link);
    QString name;
    QString link;
};

#endif // BUSMAP_H
