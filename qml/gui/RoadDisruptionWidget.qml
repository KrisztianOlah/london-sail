import QtQuick 2.0
import Sailfish.Silica 1.0



Rectangle {
    id: self
    property alias location: locationLabel.text
    property string comment: ""
    property string currentUpdate: ""
    property string severity: "Minimal"
    property int disruptionID: 0

    height: (locationLabel.paintedHeight < 150) ? 150 : (locationLabel.paintedHeight + 2*Theme.paddingMedium)
    radius: 10
    anchors {
        left: parent.left
        leftMargin: Theme.paddingLarge
        right: parent.right
        rightMargin: Theme.paddingLarge
    }
    MouseArea {
        id: mousearea
        anchors.fill: parent
        onClicked: pageStack.push(Qt.resolvedUrl("../pages/TrafficDetailsPage.qml"),
                                  {'location': self.location, 'comment': self.comment,
                                      'currentUpdate': self.currentUpdate, 'severity': self.severity,
                                      'disruptionID' : self.disruptionID})
    }

    state: severity
    Label {
        id: locationLabel
        text: "Location"
        font.bold: true
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
    }
    //These states are only used when RoadDisruptionWidgets are created,
    //they aren't changing dynamically
    states: [
        State {
            name: "Minimal"
            PropertyChanges {
                target: self
                color: "#00AD3E"
            }
        },
        State {
            name: "Moderate"
            PropertyChanges {
                target: self
                color: "#F8D42D"
            }
            PropertyChanges {
                target: locationLabel
                color: "#113B92"
            }
        },
        State {
            name: "Serious"
            PropertyChanges {
                target: self
                color: "#F86C00"
            }
        },
        State {
            name: "Severe"
            PropertyChanges {
                target: self
                color: "#E41F1F"
            }
        }
    ]
}


