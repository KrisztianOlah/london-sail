import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: self
    property string text: ""
    property int timeOut: 0
    property bool active: false

    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }
    state: "invisible"
    height: label.paintedHeight + Theme.paddingSmall * 2
    color: Theme.highlightColor
    z: 3
    Label {
        id: label
        text: self.text
        textFormat: Text.RichText
        truncationMode: TruncationMode.Fade
        font.pixelSize: Theme.fontSizeSmall
        z: 4
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        color: Theme.highlightDimmerColor
    }
    onActiveChanged: self.state = self.active ? "visible" : "invisible"
    Timer {
        interval: self.timeOut
        running: self.active
        onTriggered: {
            self.active = false
        }
    }
    states: [
        State {
            name: "visible"
            PropertyChanges {
                target: self
                opacity: 100
            }
        },
        State {
            name: "invisible"
            PropertyChanges {
                target: self
                opacity: 0
            }
        }
    ]
    transitions: [
        Transition {
            from: "visible"
            to: "invisible"
            NumberAnimation { target: self; property: "opacity"; duration: 1000; easing.type: Easing.OutSine }
        },
        Transition {
            from: "invisible"
            to: "visible"
            NumberAnimation { target: self; property: "opacity"; duration: 1000; easing.type: Easing.InSine }
        }
    ]
}
