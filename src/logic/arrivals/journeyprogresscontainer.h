#ifndef JOURNEYPROGRESSCONTAINER_H
#define JOURNEYPROGRESSCONTAINER_H

#include <QList>
#include <QObject>
#include <QPair>

class ArrivalsProxyModel;
class JourneyProgressModel;

class JourneyProgressContainer : public QObject
{
    Q_OBJECT
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
    double getDeltaTime(double) const;
    int getEta(double) const; //returns in minutes
    ArrivalsProxyModel* getModel();
    QPair<QString,double> getNextStop() const;
    void refreshData(QList<QPair<QString,double>>);
    int size() const;
    void setTime(double);
signals:
    void dataChanged();
};

#endif // JOURNEYPROGRESSCONTAINER_H
