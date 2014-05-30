import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: self
    property bool active: false
    property bool isPortrait: parent.isPortrait
    property alias title: label.text

    y: isPortrait ? (Screen.height - height) : (Screen.width - height)

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
        text: "Downloading"
        color: Theme.secondaryColor
        opacity: 0
        anchors.centerIn: parent
    }
    onActiveChanged: {
        state = active ? "active" : "inactive"
    }
    onIsPortraitChanged: {
        state = isPortrait ? "portrait" : "landscape"
    }

    states: [
        State {
            name: "portrait"
            PropertyChanges {
                target: self
                opacity: active ? 100 : 0
                y: Screen.height - height
            }
            PropertyChanges {
                target: label
                opacity: active ? 100 : 0
            }
        },
        State {
            name: "landscape"
            PropertyChanges {
                target: self
                opacity: active ? 100 : 0
                y: Screen.width - height
            }
            PropertyChanges {
                target: label
                opacity: active ? 100 : 0
            }
        },
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
            name: "downloading"
            PropertyChanges {
                target: self
                opacity: 100
            }
            PropertyChanges {
                target: label
                opacity: 100
                text: "Downloading"
            }
        },
        State {
            name: "parsing"
            PropertyChanges {
                target: self
                opacity: 100
                y: isPortrait ? (Screen.height - height) : (Screen.width - height)
            }
            PropertyChanges {
                target: label
                opacity: 100
                text: "Parsing"
            }
        }

    ]
}
