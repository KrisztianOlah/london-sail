import QtQuick 2.0
import Sailfish.Silica 1.0
import LondonSailUtilities 1.0

import "../gui"


Page {
    id: page
    allowedOrientations: Orientation.All

    property DisruptionModel disruptionModel: trafficData.getDisruptionModel()

    Component.onCompleted: trafficData.refresh()

    BusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        running: (trafficData.isDownloading() || trafficData.isParsing() )
        anchors.centerIn: parent

        Connections {
            target: trafficData
            onStateChanged: {
                if (trafficData.isDownloading() || trafficData.isParsing()) {
                    if (!view.count) { busyIndicator.running = true }
                    else {
                        refreshWidget.active = true
                    }

                }
                else {
                    busyIndicator.running = false
                    refreshWidget.active = false
                    progressLabel.text = ""
                }
            }
        }
    }

    Label {
        id: progressLabel
        text: ""
        anchors.centerIn: parent

        Connections {
            target: trafficData
            onDownloadProgress: {
                if(!view.count) {
                    progressLabel.text = value + ' bytes'
                }
            }
            onStateChanged: {
                //BUG this doesn't get displayed due to the high CPU use of xml parser
                if (trafficData.isParsing()) { progressLabel.text = "Parsing data, please wait." }
                else progressLabel = ""
            }
        }
    }

    SilicaListView {
        id: view
        anchors.fill: parent
        header: SearchHeader {
            title: "Traffic Disruptions"
            state: ""
            onFilterChanged: { disruptionModel.filter(text) }
       }

        footer: Item {
            height: Theme.paddingLarge
            width: 1
        }
        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: trafficData.refresh()
            }
        }
        PushUpMenu {
            visible: view.count
            MenuItem {
                text: "Go to top"
                onClicked: view.scrollToTop()
            }
        }

        currentIndex: -1
        model: disruptionModel
        spacing: 10
        delegate: RoadDisruptionWidget {
            location: locationData
            comment: commentsData
            currentUpdate: currentUpdateData
            severity: severityData
            disruptionID: idData

        }
        onCountChanged: {
            if (view.headerItem && view.headerItem.state === "") {
                view.headerItem.state = (view.count) ? "searchable" : ""
            }
        }

        VerticalScrollDecorator { flickable: view }

        ViewPlaceholder {
            id: placeholder
            enabled: (!busyIndicator.running && !view.count)
            text: (view.headerItem.state === "") ? "Pull down to refresh." : "No matches :("
        }
    }
    RefreshWidget {
        id: refreshWidget
    }
    onOrientationChanged: {
        //BUG: its seems to be reverted for some reason
        refreshWidget.state = isPortrait ? "landscape" : "portrait"
    }
}
