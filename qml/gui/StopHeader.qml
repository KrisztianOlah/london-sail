import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias stopIndicator: stopID.text
    property alias direction: directionLabel.text
    property alias distance: distanceLabel.text
    property bool isBusStop: false
    property string title: ""

    id: self

    anchors {
        left: parent.left
        right: parent.right
    }
    height: pageHeader.height + stopHeader.height + Theme.paddingMedium*4

    Label {
        id: pageHeader
        text: title
        font.pixelSize: Theme.fontSizeLarge
        color: Theme.highlightColor
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium*2
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }

    Rectangle {
        id: stopHeader
        height: 80
        color: Theme.secondaryHighlightColor
        opacity: 80
        anchors {
            top: pageHeader.bottom
            topMargin: Theme.paddingMedium*2
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
            text: isBusStop ? "towards" : ""
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
    states: [
        State {
            name: "visible"
//            PropertyChanges {
//                target: pageHeader
//                opacity: 0
//            }
            PropertyChanges {
                target: stopHeader
                opacity: 0
            }
            PropertyChanges {
                target: icon
                opacity: 0
            }
        },
        State {
            name: "invisible"
            PropertyChanges {
                target: stopHeader
                opacity: 100
            }
            PropertyChanges {
                target: icon
                opacity: 100
            }
        }

    ]
}
