import QtQuick 2.0
import Sailfish.Silica 1.0
import "../gui"

Page {
    id: page
    Component.onCompleted: thisWeekendData.refresh()
    allowedOrientations: Orientation.All

    BusyIndicator {
        id: busyIndicator
        running: thisWeekendData.isDownloading()
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent

        Connections {
            target: thisWeekendData
            onStateChanged: { busyIndicator.running = thisWeekendData.isDownloading() }
        }
    }

    SilicaListView {
        id: view
        anchors.fill: parent

        header: PageHeader {
            id: header
            title: "This Weekend"
        }

        footer: Rectangle {
            height: Theme.paddingLarge
            opacity: 0
        }

        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: thisWeekendData.refresh()
            }
        }


        VerticalScrollDecorator { flickable: view }

        spacing: 10
        model: thisWeekendData.getModel()
        delegate: LineInfoWidget {
            name: nameData
            statusText: statusData
            details: messageData
            color: backgroundData
            textColor: colorData
            state: "visible"
        }
        ViewPlaceholder {
            enabled: (!busyIndicator.running && !view.count)
            text: "Pull down to refresh."
        }
    }
}
