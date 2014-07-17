#include "arrivalscontainer.h"
#include <QString>
#include "arrivalsmodel.h"

ArrivalsContainer::ArrivalsContainer(ArrivalsModel* m) : model(m)
{
}


void ArrivalsContainer::add(const Vehicle& vehicle) {
    append(vehicle);
}

void ArrivalsContainer::clearData() {
    if (model) {
        model->beginReset();
    }
    clear();
    if (model) {
        model->endReset();
    }
}

void ArrivalsContainer::registerModel(ArrivalsModel* m) {
    model = m;
}

void ArrivalsContainer::replace(const ArrivalsContainer& rhs) {
    if (model) {
        model->beginReset();
        model->beginInsert(size());
    }

    if (this != &rhs) { *this = rhs; }

    if (model) {
        model->endInsert();
        model->endReset();
    }
}
