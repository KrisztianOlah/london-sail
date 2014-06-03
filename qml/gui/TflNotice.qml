import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: self
    anchors {
        left: parent.left
        right: parent.right
    }
    height: label.height + Theme.paddingMedium*2
    Item {
        id: topGap
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: Theme.paddingMedium
    }
    Label {
        id: label
        text: "Data provided by Tfl."
        font.pixelSize: Theme.fontSizeTiny
        opacity: 0
        anchors {
            top: topGap.bottom
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: 120
        }
    }
    Item {
        anchors {
            left: parent.left
            right: parent.right
            top: label.bottom
            bottom: parent.bottom
        }
    }
    states: [
        State {
            name: "invisible"
            PropertyChanges {
                target: label
                opacity: 0
            }
        },
        State {
            name: "visible"
            PropertyChanges {
                target: label
                opacity: 100
            }
        }

    ]
}
