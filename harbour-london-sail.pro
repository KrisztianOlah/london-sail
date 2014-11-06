# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = harbour-london-sail

CONFIG += sailfishapp

QMAKE_CXXFLAGS += -std=c++0x

QT += network xml sql

SOURCES += src/harbour-london-sail.cpp \
    src/logic/servicestatuslogic.cpp \
    src/logic/thisweekendlogic.cpp \
    src/logic/serviceStatus/thisweekendxmlhandler.cpp \
    src/logic/serviceStatus/thisweekendlinemodel.cpp \
    src/logic/serviceStatus/linewrapper.cpp \
    src/logic/serviceStatus/servicestatusxmlhandler.cpp \
    src/logic/trafficlogic.cpp \
    src/logic/traffic/street.cpp \
    src/logic/traffic/disruption.cpp \
    src/logic/traffic/trafficcontainer.cpp \
    src/logic/traffic/disruptionmodel.cpp \
    src/logic/traffic/streetmodel.cpp \
    src/logic/traffic/disruptionproxymodel.cpp \
    src/logic/traffic/trafficxmlreader.cpp \
    src/logic/serviceStatus/servicestatusproxymodel.cpp \
    src/logic/arrivalslogic.cpp \
    src/logic/arrivals/arrivalsmodel.cpp \
    src/logic/arrivals/arrivalscontainer.cpp \
    src/logic/arrivals/vehicle.cpp \
    src/logic/arrivals/stop.cpp \
    src/logic/arrivals/arrivalsproxymodel.cpp \
    src/logic/arrivals/journeyprogressmodel.cpp \
    src/logic/arrivals/journeyprogresscontainer.cpp \
    src/logic/coverlogic.cpp \
    src/logic/database/databasemanager.cpp \
    src/logic/database/database.cpp \
    src/logic/arrivals/stopsquerymodel.cpp \
    src/logic/maplogic.cpp \
    src/logic/maps/mapsmodel.cpp \
    src/logic/maps/busmap.cpp \
    src/logic/maps/busmapdownloader.cpp \
    src/logic/maps/mapfilesmodel.cpp

OTHER_FILES += qml/harbour-london-sail.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/harbour-london-sail.spec \
    rpm/harbour-london-sail.yaml \
    harbour-london-sail.desktop \
    qml/pages/ServiceStatusPage.qml \
    qml/gui/LineInfoWidget.qml \
    qml/gui/InfoIcon.qml \
    qml/pages/AboutPage.qml \
    qml/pages/TubeMapPage.qml \
    qml/pages/ChangelogPage.qml \
    qml/pages/LicensePage.qml \
    qml/pages/ThisWeekPage.qml \
    qml/pages/TrafficPage.qml \
    qml/gui/RoadDisruptionWidget.qml \
    qml/pages/TrafficDetailsPage.qml \
    qml/gui/RoadDetailsWidget.qml \
    qml/gui/StreetWidget.qml \
    qml/gui/SearchHeader.qml \
    qml/gui/RefreshWidget.qml \
    qml/gui/TflNotice.qml \
    qml/pages/DeparturePage.qml \
    qml/pages/BusStopPage.qml \
    qml/gui/StopInfoWidget.qml \
    qml/gui/StopHeader.qml \
    qml/gui/BusWidget.qml \
    qml/cover/ArrivalsCover.qml \
    qml/pages/JourneyProgressPage.qml \
    qml/cover/JourneyProgressCover.qml \
    qml/gui/StopIcon.qml \
    qml/gui/RunningText.qml \
    qml/pages/MapsPage.qml \
    qml/pages/BusMapsPage.qml \
    qml/pages/MyMapsPage.qml \
    qml/gui/NotificationWidget.qml \
    qml/gui/TrafficSearchHeader.qml

HEADERS += \
    src/logic/servicestatuslogic.h \
    src/logic/thisweekendlogic.h \
    src/logic/serviceStatus/thisweekendxmlhandler.h \
    src/logic/serviceStatus/thisweekendlinemodel.h \
    src/logic/serviceStatus/linewrapper.h \
    src/logic/serviceStatus/servicestatusxmlhandler.h \
    src/logic/trafficlogic.h \
    src/logic/traffic/street.h \
    src/logic/traffic/disruption.h \
    src/logic/traffic/trafficcontainer.h \
    src/logic/traffic/disruptionmodel.h \
    src/logic/traffic/streetmodel.h \
    src/logic/traffic/disruptionproxymodel.h \
    src/logic/traffic/trafficxmlreader.h \
    src/logic/serviceStatus/servicestatusproxymodel.h \
    src/logic/arrivalslogic.h \
    src/logic/arrivals/arrivalsmodel.h \
    src/logic/arrivals/arrivalscontainer.h \
    src/logic/arrivals/vehicle.h \
    src/logic/arrivals/stop.h \
    src/logic/arrivals/arrivalsproxymodel.h \
    src/logic/arrivals/journeyprogressmodel.h \
    src/logic/arrivals/journeyprogresscontainer.h \
    src/logic/coverlogic.h \
    src/logic/database/databasemanager.h \
    src/logic/database/database.h \
    src/logic/arrivals/stopsquerymodel.h \
    src/logic/maplogic.h \
    src/logic/maps/mapsmodel.h \
    src/logic/maps/busmap.h \
    src/logic/maps/busmapdownloader.h \
    src/logic/maps/mapfilesmodel.h

RESOURCES += \
    images.qrc

