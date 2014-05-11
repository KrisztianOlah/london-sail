import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: self
    property bool active: false
    property alias title: label.text

    y: parent.isPortrait ? (Screen.height - height) : (Screen.width - height)

    anchors {
        left: parent.left
        right: parent.right
    }

    height: 100
    color: Theme.secondaryHighlightColor
    opacity: 0

    Item {
        height: parent.height
        width: parent.height
        anchors {
            left: parent.left
            leftMargin: Theme.paddingExtraLarge
        }

        BusyIndicator {
            running: active
            size: BusyIndicatorSize.Medium
            anchors.centerIn: parent
        }
    }


    Label {
        id: label
        text: "Refreshing"
        color: Theme.highlightColor
        opacity: 0
        anchors.centerIn: parent
    }
    onActiveChanged: {
        state = active ? "active" : "inactive"
    }

    states: [
        State {
            name: "active"
            PropertyChanges {
                target: self
                opacity: 100
            }
            PropertyChanges {
                target: label
                opacity: 100
            }
        },
        State {
            name: "inactive"
            PropertyChanges {
                target: self
                opacity: 0
            }
            PropertyChanges {
                target: label
                opacity: 0
            }
        },
        State {
            name: "portrait"
            PropertyChanges {
                target: self
                y: Screen.height - height
            }
        },
        State {
            name: "landscape"
            PropertyChanges {
                target: self
                y: Screen.width - height
            }
        }

    ]
}
