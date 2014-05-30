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

QT += network xml

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
    src/logic/traffic/trafficxmlreader.cpp

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
    qml/gui/RefreshWidget.qml

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
    src/utilities/utility.h \
    src/logic/traffic/trafficcontainer.h \
    src/logic/traffic/disruptionmodel.h \
    src/logic/traffic/streetmodel.h \
    src/logic/traffic/disruptionproxymodel.h \
    src/logic/traffic/trafficxmlreader.h

RESOURCES += \
    images.qrc

