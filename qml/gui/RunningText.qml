/*
Copyright (C) 2014 Krisztian Olah

  email: fasza2mobile@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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
