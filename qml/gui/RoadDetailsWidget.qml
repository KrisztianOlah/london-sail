import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias location: locationLabel.text
    property alias comment: commentLabel.text
    property alias currentUpdate: currentUpdateLabel.text
    id: self
    height: locationLabel.paintedHeight + commentLabel.paintedHeight + currentUpdateLabel.paintedHeight + 2*Theme.paddingMedium
    radius: 10
    anchors {
        left: parent.left
        leftMargin: Theme.paddingLarge
        right: parent.right
        rightMargin: Theme.paddingLarge
    }
    state: "Minimal"
    Label {
        id: locationLabel
        text: "Location"
        font.bold: true
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge

        }
    }
    Label {
        id: commentLabel
        text: ""
        font.pixelSize: Theme.fontSizeSmall

        wrapMode: Text.WordWrap
        anchors {
            top: locationLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }
    Label {
        id: currentUpdateLabel
        text: ""
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        anchors {
            top: commentLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }

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
            PropertyChanges {
                target: commentLabel
                color: "#113B92"
            }
            PropertyChanges {
                target: currentUpdateLabel
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
