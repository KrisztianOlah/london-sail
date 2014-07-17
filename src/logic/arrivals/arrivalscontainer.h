#ifndef ARRIVALSCONTAINER_H
#define ARRIVALSCONTAINER_H

#include <QList>
#include "vehicle.h"

class QString;
class ArrivalsModel;

class ArrivalsContainer : public QList<Vehicle>
{
public:
    ArrivalsContainer(ArrivalsModel* = 0);
private:
    ArrivalsModel* model;
public:
    void add(const Vehicle& vehicle);
    void clearData();
    void registerModel(ArrivalsModel*);
    void replace(const ArrivalsContainer& rhs);

};

#endif // ARRIVALSCONTAINER_H
