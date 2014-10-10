import QtQuick 2.0
import Sailfish.Silica 1.0
import "../gui"


Page {
    id: page
    allowedOrientations: Orientation.All
    property var boroughs: ["Barking and Dagenham", "Barnet", "Bexley", "Brent", "Bromley", "Camden", "City of London", "Croydon", "Ealing",
                    "Enfield", "Greenwich", "Hackney", "Hammersmith and Fulham", "Haringey", "Harrow", "Havering", "Hillingdon",
                    "Hounslow", "Islington", "Kensington and Chelsea", "Kingston upon Thames", "Lambeth", "Lewisham", "Merton",
                    "Newham", "Redbridge", "Richmond", "Southwark", "Sutton", "Tower Hamlets", "Waltham Forest", "Wandsworth", "Westminster"]
    SilicaListView {
        id: view
        anchors.fill: parent
        PullDownMenu {
            MenuItem {
                text: "My Bus Maps"
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("MyMapsPage.qml"))
                }
            }
            MenuItem {
                text: "Show Underground Map"
                onClicked: pageStack.push(Qt.resolvedUrl("TubeMapPage.qml"))
            }
        }
        header: Item {
            function readInput(text) {
                pageStack.push(Qt.resolvedUrl("BusMapsPage.qml"), { 'headertitle' : text })
            }

            height: 150 + pageHeader.height
            anchors {
                left: parent.left
                right: parent.right
            }
            VerticalScrollDecorator {
                flickable: view
            }
            Label {
                id: pageHeader
                text: "Bus Maps"
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeLarge
                horizontalAlignment: Text.AlignRight
                anchors {
                    top: parent.top
                    topMargin: Theme.paddingMedium*2
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
            }

            SearchField {
                id: searchfield
                placeholderText: "By Route"
                EnterKey.onClicked: readInput(text)
                anchors {
                    top: pageHeader.bottom
                    topMargin: Theme.paddingMedium*2
                    left: parent.left
                    leftMargin: Theme.paddingMedium
                    right: parent.right
                    rightMargin: Theme.paddingMedium
                }

            }
        }
        footer: Item {
            height: Theme.paddingLarge
            width: 1
        }
        model: boroughs
        delegate: BackgroundItem {
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    verticalCenter: parent.verticalCenter
                }
                text: boroughs[index]
            }
            onClicked: {
                pageStack.push(Qt.resolvedUrl("BusMapsPage.qml"), { 'headertitle' : boroughs[index] })
            }
        }
        VerticalScrollDecorator {
            flickable: view
        }
    }
}

