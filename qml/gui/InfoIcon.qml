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

//this component is a little circle with an 'i' in the middle which is to be displayed when
//LineInfoWidget is expandable to a detailed view, sort of a visual aid for user

Rectangle {
    id: circle
    property color iconColor: "#FFFFFF"
    property int size: 20

    width: size
    height: size
    radius: size/2
    border.width: 1
    border.color: iconColor
    state: "invisible"
    Label {
        id: label
        text: "i"
        color: iconColor
        font.pixelSize: Theme.fontSizeExtraSmall
        anchors.centerIn: parent
    }
    states: [
        State {
            name: "visible"
            PropertyChanges {
                target: circle
                opacity: 100
            }
            PropertyChanges {
                target: label
                opacity: 100
            }
        },
        State {
            name: "invisible"
            PropertyChanges {
                target: circle
                opacity: 0
            }
            PropertyChanges {
                target: label
                opacity: 0
            }
        }

    ]
    Behavior on opacity {
        FadeAnimation {}
    }
}
