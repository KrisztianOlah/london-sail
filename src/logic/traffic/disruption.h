#ifndef DISRUPTION_H
#define DISRUPTION_H

#include <QString>

struct Disruption
{
    Disruption();

//    enum Status { Active, ActiveLT, Scheduled, Recurring,  Cleared };
//    enum Interest { Low, Medium, High };

    int id;
    QString category;
    QString coordinates;
    QString comments;
    QString currentUpdate;
    QString endTime;//QDateTime
    QString lastModTime;//QDateTime
    QString levelOfInterest;//can be used later to deterine a score by which data can be displayed
    QString location;
    QString severity;
    QString remarkTime;//QDateTime //Time of currentupdate
    QString startTime;//QDateTime
    QString status;
    QString subCategory;
};

#endif // DISRUPTION_H

