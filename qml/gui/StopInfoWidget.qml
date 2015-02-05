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

Rectangle {
    property alias distance: distanceLabel.text
    property alias name: nameLabel.text
    property int type: 0
    property string indicator: ""//TODO rename
    property string towards: ""
    property string code: ""
    property string rank: ""
    property bool isFavorite: arrivalsData.isStopFavorite(code)
    property bool isDragable: false

    id: self
    height: nameLabel.paintedHeight + towardLabel.paintedHeight + Theme.paddingMedium * 2
    radius: 10
    color: isDragable ? Theme.highlightBackgroundColor : Theme.secondaryHighlightColor
    Behavior on color { ColorAnimation { duration: 100 } }

    StopIcon {
        id: icon
        stopPointIndicator: indicator
        type: self.type
        anchors {
            left: parent.left
            leftMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
    }

    Label {
        id: nameLabel
        text: "Name of Stop"
        wrapMode: Text.WordWrap
        font.pixelSize: Theme.fontSizeMedium
        anchors {
            top: parent.top
            //no need to leave space when there is nothing to display
            topMargin: (towards === "") ? (parent.height - nameLabel.paintedHeight) / 2 : Theme.paddingMedium
            left: icon.right
            leftMargin: Theme.paddingMedium
            right: iconButton.left
            rightMargin: Theme.paddingMedium

        }
    }
    Label {
        id: towardLabel
        text: towards
        wrapMode: Text.WordWrap
        font.pixelSize: Theme.fontSizeExtraSmall
        anchors {
            top: nameLabel.bottom
            left: icon.right
            leftMargin: Theme.paddingMedium
            right: iconButton.left
            rightMargin: Theme.paddingMedium
        }
    }

    Label {
        id: distanceLabel
        text: rank
        font.pixelSize: Theme.fontSizeExtraSmall
        anchors {
            top: icon.bottom
//            topMargin: 2//Theme.fontSizeLarge
            left: parent.left
            leftMargin: 10
        }
    }
    IconButton {
        id: iconButton
        icon.source: isFavorite ? "image://theme/icon-l-favorite" : "image://theme/icon-l-star"
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
        }
        onClicked: {
            if (isFavorite) {
                arrivalsData.favorStop(code, false)
            }
            else {
                arrivalsData.favorStop(code, true)
            }
            isFavorite = arrivalsData.isStopFavorite(code)
        }
    }
}
