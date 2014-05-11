#ifndef STREET_H
#define STREET_H

#include <QString>

//This struct is just to hold a Street object from our feed
struct Street
{
    Street() = default;
    Street(const QString&, const QString&, const QString&);

    QString closure;
    QString directions;
    QString name;
};

#endif // STREET_H
