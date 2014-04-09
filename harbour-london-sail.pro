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
    src/logic/servicestatusxmlhandler.cpp \
    src/logic/thisweekendlogic.cpp \
    src/logic/serviceStatus/thisweekendxmlhandler.cpp \
    src/logic/serviceStatus/thisweekendlinemodel.cpp \
    src/logic/serviceStatus/linewrapper.cpp

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
    qml/pages/ThisWeekPage.qml

HEADERS += \
    src/logic/servicestatuslogic.h \
    src/logic/servicestatusxmlhandler.h \
    src/logic/thisweekendlogic.h \
    src/logic/serviceStatus/thisweekendxmlhandler.h \
    src/logic/serviceStatus/thisweekendlinemodel.h \
    src/logic/serviceStatus/linewrapper.h

RESOURCES += \
    images.qrc

