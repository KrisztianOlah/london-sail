/*
Copyright (C) 2014 Krisztian Olah

  email: fasza2mobile@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QCoreApplication>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QtQml>
#include <QQmlContext>
#include <QQuickView>
#include <sailfishapp.h>
#include "logic/arrivals/arrivalsproxymodel.h"
#include "logic/arrivals/stop.h"
#include "logic/arrivals/stopsquerymodel.h"
#include "logic/arrivalslogic.h"
#include "logic/coverlogic.h"
#include "logic/database/databasemanager.h"
#include "logic/maplogic.h"
#include "logic/maps/mapfilesmodel.h"
#include "logic/maps/mapsmodel.h"
#include "logic/servicestatuslogic.h"
#include "logic/serviceStatus/servicestatusproxymodel.h"
#include "logic/serviceStatus/thisweekendlinemodel.h"
#include "logic/traffic/disruptionproxymodel.h"
#include "logic/traffic/streetmodel.h"
#include "logic/thisweekendlogic.h"
#include "logic/trafficlogic.h"

int main(int argc, char *argv[])
{
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file

    QGuiApplication* app = SailfishApp::application(argc, argv);
    app->setOrganizationName("");
    QQuickView* view = SailfishApp::createView();
    view->setSource(SailfishApp::pathTo("qml/harbour-london-sail.qml"));

    //use 1 global QNetworkAccessManager object for all our network needs
    //on the heap so that it can be the parent of serviceLogic
    QScopedPointer<QNetworkAccessManager> networkMngr(new QNetworkAccessManager());
    QScopedPointer<DatabaseManager> databaseManager(new DatabaseManager());

    qmlRegisterType<ServiceStatusProxyModel>("harbour.london.sail.utilities",1,0, "ServiceStatusModel");
    ServiceStatusLogic* serviceLogic = new ServiceStatusLogic(networkMngr.data());
    view->rootContext()->setContextProperty("serviceStatusData", serviceLogic);

    qmlRegisterType<ThisWeekendLineModel>("harbour.london.sail.utilities",1,0,"WeekendModel");
    ThisWeekendLogic* weekendLogic = new ThisWeekendLogic(networkMngr.data());
    view->rootContext()->setContextProperty("thisWeekendData", weekendLogic);

    qmlRegisterType<DisruptionProxyModel>("harbour.london.sail.utilities",1,0,"DisruptionModel");
    qmlRegisterType<StreetModel>("harbour.london.sail.utilities",1,0,"StreetModel");
    TrafficLogic* trafficLogic = new TrafficLogic(networkMngr.data());
    view->rootContext()->setContextProperty("trafficData", trafficLogic);

    qmlRegisterType<ArrivalsProxyModel>("harbour.london.sail.utilities",1,0,"ArrivalsModel");
    qmlRegisterType<StopsQueryModel>("harbour.london.sail.utilities",1,0,"StopsModel");
    qmlRegisterType<Stop>("harbour.london.sail.utilities",1,0,"Stop");
    ArrivalsLogic* arrivalsLogic = new ArrivalsLogic(databaseManager.data(),networkMngr.data());
    view->rootContext()->setContextProperty("arrivalsData", arrivalsLogic);

    qmlRegisterType<CoverLogic>("harbour.london.sail.utilities",1,0,"PageCodes");
    CoverLogic* coverLogic = new CoverLogic();
    view->rootContext()->setContextProperty("coverData", coverLogic);

    qmlRegisterType<MapFilesModel>("harbour.london.sail.utilities",1,0,"FilesModel");

    qmlRegisterType<MapsModel>("harbour.london.sail.utilities",1,0,"MapsModel");
    MapLogic* mapLogic = new MapLogic(networkMngr.data());
    view->rootContext()->setContextProperty("mapData", mapLogic);

    view->show();

    return app->exec();
}

