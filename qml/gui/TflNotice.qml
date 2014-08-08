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
        text: "Data provided by TfL."
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
