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
    property alias stopIndicator: stopID.text
    property alias direction: directionLabel.text
    property alias distance: distanceLabel.text
    property int type: 0
    property string title: ""

    id: self

    anchors {
        left: parent.left
        right: parent.right
    }
    height: pageHeader.height + stopHeader.height + Theme.paddingMedium*4

    Label {
        id: pageHeader
        text: title
        font.pixelSize: Theme.fontSizeLarge
        color: Theme.highlightColor
        horizontalAlignment: Text.AlignRight
        wrapMode: Text.WordWrap
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium*2
            right: parent.right
            rightMargin: Theme.paddingLarge
            left: parent.left
            leftMargin: 100
        }
    }

    Rectangle {
        id: stopHeader
        height: directionLabel.paintedHeight + Theme.paddingMedium*2
        color: Theme.secondaryHighlightColor
        opacity: 80
        anchors {
            top: pageHeader.bottom
            topMargin: Theme.paddingMedium*2
            left: parent.left
            right: parent.right
        }

        Image  {
            id: waves
            source: "qrc:///waves.png"
            visible: (type === Stop.River) ? true : false
            anchors {
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: icon
            height: 50
            width: 50
            radius: 25
            color: (type === Stop.Bus) ? "red" : "blue"
            visible: (type === Stop.Bus) ? true : false
            anchors {
                left: parent.left
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
            Label {
                id: stopID
                anchors.centerIn: parent
                text: ""
            }
        }

        Label {
            id: towardsLabel
            text: (directionLabel.text !== "" && (type === Stop.Bus || type === Stop.River)) ? "towards" : ""
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.highlightColor
            anchors {
                left: waves.right
                leftMargin: Theme.paddingExtraLarge
                top: parent.top
                topMargin: Theme.paddingSmall
            }
        }
        Label {
            id: directionLabel
            text: ""
            color: Theme.highlightColor
            wrapMode: Text.WordWrap
            anchors {
                left: towardsLabel.right
                leftMargin: Theme.paddingSmall
                right: parent.right
                rightMargin: Theme.paddingLarge
            }
        }


        Label {
            id: distanceLabel
            text: ""
            font.pixelSize: Theme.fontSizeExtraSmall
            color: Theme.highlightColor
            anchors {
                right: parent.right
                bottom: parent.bottom
            }
        }
    }
    states: [

        State {
            name: "invisible"
            PropertyChanges {
                target: stopHeader
                opacity: 0
            }
            PropertyChanges {
                target: icon
                opacity: 0
            }
        },
        State {
            name: "visible"
            PropertyChanges {
                target: stopHeader
                opacity: 100
            }
            PropertyChanges {
                target: icon
                opacity: 100
            }
        }

    ]
    onTitleChanged: { state = title === "" ? "invisible" : "visible" }
}
