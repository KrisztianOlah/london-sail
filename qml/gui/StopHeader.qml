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
    property Stop currentStop: arrivalsData.getCurrentStop()
    property string stopPointIndicator: currentStop.getStopPointIndicator()
    property string direction: currentStop.getTowards()
    property alias distance: distanceLabel.text
    property string stopCode: currentStop.getID()
    property int type: currentStop.getType()
    property string title: currentStop.getName()
    property bool isFavorite: arrivalsData.isStopFavorite(stopCode)

    Connections {
        target: self.currentStop
        onDataChanged: {
            self.stopPointIndicator = currentStop.getStopPointIndicator()
            self.direction = currentStop.getTowards()
            self.distance = distanceLabel.text
            self.stopCode = currentStop.getID()
            self.type = currentStop.getType()
            self.title = currentStop.getName()
            self.isFavorite = arrivalsData.isStopFavorite(stopCode)

        }
    }

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
            leftMargin: 130
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

        StopIcon {
            id: icon
            stopPointIndicator: self.stopPointIndicator
            type: self.type
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: Theme.paddingSmall
            }
        }

        IconButton {
            id: favoriteButton
            icon.source: isFavorite ? "image://theme/icon-l-favorite" : "image://theme/icon-l-star"
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            onClicked: {
                if (!isFavorite) {
                    self.currentStop.addToDb(true)//won't do anything if record is already in db
                    arrivalsData.favorStop(stopCode, true)//make sure it is favorite in case record was already in db
                    isFavorite = arrivalsData.isStopFavorite(stopCode)
                }
                else {
                    arrivalsData.favorStop(stopCode, false)
                    isFavorite = arrivalsData.isStopFavorite(stopCode)
                }
            }
        }

        Label {
            id: towardsLabel
            text: (directionLabel.text !== "" && (type === Stop.Bus || type === Stop.River)) ? "towards" : ""
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.highlightColor
            anchors {
                left: icon.right
                leftMargin: Theme.paddingExtraLarge
                top: parent.top
                topMargin: Theme.paddingSmall
            }
        }

        Label {
            id: directionLabel
            text: currentStop.getTowards()//""
            color: Theme.highlightColor
            wrapMode: Text.WordWrap
            anchors {
                left: towardsLabel.right
                leftMargin: Theme.paddingSmall
                right: favoriteButton.left
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
    transitions: [
        Transition {
            from: "invisible"
            to: "visible"
            FadeAnimation {
                target: self
            }
        },
        Transition {
            from: "visible"
            to: "invisible"
            FadeAnimation {
                target: self
            }
        }
    ]
    onTitleChanged: { state = (title === "") ? "invisible" : "visible" }
}
