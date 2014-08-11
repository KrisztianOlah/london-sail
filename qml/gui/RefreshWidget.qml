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
    property bool active: false
    property bool isPortrait: parent.isPortrait
    property alias title: label.text

    y: isPortrait ? (Screen.height - height) : (Screen.width - height)

    anchors {
        left: parent.left
        right: parent.right
    }

    height: 0
    color: Theme.secondaryHighlightColor
    opacity: 0
    state: "inactive"

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
        text: ""
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
                height: active ? 100 : 0
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
                height: active ? 100 : 0
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
                height: 100
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
                height: 0
                opacity: 0
            }
            PropertyChanges {
                target: label
                opacity: 0
            }
        }
    ]
    transitions: [
        Transition {
            from: "inactive"
            to: "active"
            NumberAnimation { target: self; properties: "height"; duration: 300 }
        },
        Transition {
            from: "active"
            to: "inactive"
            NumberAnimation { target: self; properties: "height"; duration: 300 }
            NumberAnimation { target: self; properties: "opacity" ; duration: 300 }
        }
    ]
}
