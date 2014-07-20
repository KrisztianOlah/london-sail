#ifndef JOURNEYPROGRESSCONTAINER_H
#define JOURNEYPROGRESSCONTAINER_H

#include <QList>
#include <QObject>
#include <QPair>

class ArrivalsProxyModel;
class JourneyProgressModel;

class JourneyProgressContainer : public QObject
{
public:
    explicit JourneyProgressContainer(QObject* parent);
private:
    QList<QPair<QString,double>> data;
    double time;
    JourneyProgressModel* model;
    ArrivalsProxyModel* proxyModel;
public:
    QPair<QString,double> at(int index) const;
    void clear();
    int getEta(double) const; //returns in minutes
    double getDeltaTime(double) const;//for sorting
   ArrivalsProxyModel* getModel();
    void refreshData(QList<QPair<QString,double>>);
    int size() const;
    void setTime(double);
};

#endif // JOURNEYPROGRESSCONTAINER_H
