import QtQuick 2.0
import Sailfish.Silica 1.0
import LondonSailUtilities 1.0
import "../gui"

Page {
    id: page
    allowedOrientations: Orientation.All

    property string location: ""
    property string comment: ""
    property string currentUpdate: ""
    property string severity: ""
    property int disruptionID: 0
    property StreetModel streetModel: trafficData.getStreetModel(disruptionID)
    SilicaFlickable {
        id: flick
        anchors.fill: parent

        contentHeight: column.height

        state: (streetModel.count() ) ? "visibleStreets" : "invisibleStreets"

        VerticalScrollDecorator { flickable: flick }

        Column {
            id: column
            width: page.width
            spacing: 10

            PageHeader {
                title: "Disruption Details"
            }

            RoadDetailsWidget {
                id: detailsWidget
                location: page.location
                comment: page.comment
                currentUpdate: page.currentUpdate
                state: page.severity
            }
            Item {
                id: topExtraSpace
                height: 30
                width: 1
            }

            Label {
                id: secondaryHeader
                text: "Affected Roads/Streets"
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor
                anchors {
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
            }
            Item {
                id: middleExtraSpace
                height: 30
                width: 1
            }

            Repeater {
                model: streetModel
                StreetWidget {
                    name: nameData
                    closure: closureData
                    direction: directionsData
                }
            }
            Item {
                id: bottomExtraSpace
                height: Theme.paddingLarge
                width: 1
            }
        }
        states: [
            State {
            name: "visibleStreets"
            PropertyChanges {
                target: secondaryHeader
                opacity: 100
            }
            PropertyChanges {
                target: topExtraSpace
                width: 1
            }
            PropertyChanges {
                target: middleExtraSpace
                width: 1
            }
            PropertyChanges {
                target: bottomExtraSpace
                width: 1
            }
        },
        State {
                name: "invisibleStreets"
                PropertyChanges {
                    target: secondaryHeader
                    opacity: 0
                    height: Theme.paddingLarge
                }
                PropertyChanges {
                    target: topExtraSpace
                    width: 0
                }
                PropertyChanges {
                    target: middleExtraSpace
                    width: 0
                }
                PropertyChanges {
                    target: bottomExtraSpace
                    width: 0
                }
            }
        ]
    }
}
