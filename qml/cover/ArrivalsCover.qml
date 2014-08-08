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
import "../gui"

Item {
    property bool active: false
    property ArrivalsModel arrivalsModel: arrivalsData.getArrivalsModel()
    anchors.fill: parent

    ListView {
        id: view
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium
            bottom: parent.bottom
            left: parent.left
            leftMargin: 40
            right: parent.right
            rightMargin: 40
        }
        model: arrivalsModel
        delegate: Item {
            anchors {
                left: parent.left
                right: parent.right
            }
            height: lineLabel.paintedHeight

            Label {
                id: lineLabel
                text: lineData
                color: Theme.highlightColor
                anchors.left: parent.left
            }
            Label {
                id: etaLabel
                text: etaData < 2 ? "due" : etaData + "min"
                horizontalAlignment: Text.AlignRight
                anchors.right: parent.right
            }
        }
    }
//    onActiveChanged: {
//        if (!active) {
//            v
//        }
//    }

//    Label {
//        anchors.centerIn: parent
//        text: active ? "I'm active!" : "I'm sleeping"
//        RotationAnimation on rotation {
//            running: active
//            duration: 1000
//            loops: Animation.Infinite
//            from: 0; to: 360
//        }
//    }
}
