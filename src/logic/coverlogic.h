#ifndef COVERLOGIC_H
#define COVERLOGIC_H

#include <QObject>

class CoverLogic : public QObject
{
    Q_OBJECT
    Q_ENUMS(PageType)
public:
    enum PageType { None, BusStopPage, JourneyProgressPage };
    explicit CoverLogic(QObject *parent = 0);
private:
    int currentPage;
signals:
    void pageChanged();
public slots:
    int getCurrentPage();
    void reportPage(int);

};

#endif // COVERLOGIC_H
