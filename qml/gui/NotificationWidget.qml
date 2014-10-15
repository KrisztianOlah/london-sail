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
