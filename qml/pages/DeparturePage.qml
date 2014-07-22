import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0
import "../gui"

//TODO add "Data provided by Transport for London"
//TODO user to be able to set radius
Page {
    id: page
    onStatusChanged: {
                if (status === PageStatus.Active) { coverData.reportPage(PageCodes.None) }
    }

    SilicaListView {
        id: view
        anchors.fill: parent

        //replace by SearchHeader
        header: PageHeader {
            title: "Departures"
        }
        footer: TflNotice {}
        PullDownMenu {
            id: pulley
            MenuItem {
                text: "Check Bus Stop by code"
            }
            MenuItem {
                text: "Search bus stop by name"
            }
            MenuItem {
                text: "Here"
                enabled: false
                visible: false
            }
        }

        spacing: 10
        model: 10//myModel
        delegate: StopInfoWidget {
//            name: nameData
//            indicator: indicatorData
//            towards: "towards " + towardsData
//            distance: distanceData + "m"
            onClicked: {
                pageStack.push(Qt.resolvedUrl("BusStopPage.qml")) //use codeData to get info on stop/station
            }
        }
        ViewPlaceholder {
            text: "Pull down to enter for Bus Stop's code."
        }
    }
}
