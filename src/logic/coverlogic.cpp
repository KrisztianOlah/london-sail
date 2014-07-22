#include "coverlogic.h"
#include <QDebug>

CoverLogic::CoverLogic(QObject *parent) :
    QObject(parent)
{
}

//public slots:
int CoverLogic::getCurrentPage() { return currentPage; }

void CoverLogic::reportPage(int page) {
    currentPage = page;
    emit pageChanged();
}
