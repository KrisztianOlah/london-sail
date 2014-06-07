import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias stopSign: stopID.text
    property alias direction: directionLabel.text
    property alias distance: distanceLabel.text

    id: self
    height: 80
    color: Theme.secondaryHighlightColor
    opacity: 80
    anchors {
        left: parent.left
        right: parent.right
    }

    Rectangle {
        id: icon
        height: 50
        width: 50
        radius: 25
        color: "red"
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        Label {
            id: stopID
            anchors.centerIn: parent
            text: ""
        }
    }
    Label {
        id: directionLabel
        text: ""
//        font.pixelSize: Theme.fontSizeLarge
        color: Theme.highlightColor
        anchors.centerIn: parent
    }
    Label {
        id: towardsLabel
        text: "towards"
        font.pixelSize: Theme.fontSizeTiny
        color: Theme.highlightColor
        anchors {
            right: directionLabel.left
            top: parent.top
            topMargin: Theme.paddingSmall
//            verticalCenter: parent.verticalCenter
        }
    }

    Label {
        id: distanceLabel
        text: ""
        font.pixelSize: Theme.fontSizeExtraSmall
        color: Theme.highlightColor
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
    }
}
