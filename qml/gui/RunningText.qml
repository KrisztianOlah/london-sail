import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0

Item {
    id: self
    property color backgroundColor: Theme.highlightColor
    property double backgroundOpacity: 0.4
    property color textColor: Theme.highlightDimmerColor

    state: (messageLabel.text === "") ? "invisible" : "visible"
    Connections {
        target: arrivalsData
        onCurrentStopMessagesChanged: {
            messageLabel.text = arrivalsData.getCurrentStopMessages()
        }
    }

    Rectangle {
        id: shade
        color: backgroundColor
        opacity: backgroundOpacity
        anchors.fill: parent
//        Component.onDestruction: {
//            console.log("")
//        }

        Label {
            id: messageLabel
            color: textColor
            clip: true
            text: arrivalsData.getCurrentStopMessages()
            anchors.verticalCenter: parent.verticalCenter

//            Component.onCompleted: {
//                console.log("**** speed: " + (messageLabel.paintedWidth - self.width) )
//            }


            onTextChanged: {
                state = (messageLabel.text === "") ? "invisible" : "visible"
                arrivalsData.refreshArrivalsModel()
            }
        }
        NumberAnimation {
            id: animation
            target: messageLabel
            from: parent.width
            to: 0 - messageLabel.paintedWidth
            //should have the same speed for any length text
            duration: (messageLabel.paintedWidth + self.width) * 5
            property: "x"
            running: true
            loops: Animation.Infinite
        }

    }

    OpacityRampEffect {
        sourceItem: shade
        direction: OpacityRamp.RightToLeft
        slope: 0.5
        offset: 0.001
    }

    states: [
        State {
            name: "visible"
            PropertyChanges {
                target: self
                height: 50
            }
        },
        State {
            name: "invisible"
            PropertyChanges {
                target: self
                height: 0
            }
        }

    ]
}
