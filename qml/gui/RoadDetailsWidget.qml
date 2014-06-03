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
    property alias location: locationLabel.text
    property alias comment: commentLabel.text
    property alias currentUpdate: currentUpdateLabel.text
    id: self
    height: locationLabel.paintedHeight + commentLabel.paintedHeight + currentUpdateLabel.paintedHeight + updateTag.paintedHeight
            + 3*Theme.paddingMedium
    radius: 10
    anchors {
        left: parent.left
        leftMargin: Theme.paddingLarge
        right: parent.right
        rightMargin: Theme.paddingLarge
    }
    state: "Minimal"
    Label {
        id: locationLabel
        text: "Location"
        font.bold: true
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge

        }
    }
    Label {
        id: commentLabel
        text: ""
        font.pixelSize: Theme.fontSizeSmall

        wrapMode: Text.WordWrap
        anchors {
            top: locationLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }
    Label {
        id: updateTag
        font.italic: true
        font.pixelSize: Theme.fontSizeExtraSmall
        text: currentUpdateLabel.text !== "" ? "Latest updates:" : ""
        anchors {
            top: commentLabel.bottom
            topMargin: Theme.paddingMedium
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }

    Label {
        id: currentUpdateLabel
        text: ""
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        anchors {
            top: updateTag.bottom
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }

    states: [
        State {
            name: "Minimal"
            PropertyChanges {
                target: self
                color: "#00AD3E"
            }
        },
        State {
            name: "Moderate"
            PropertyChanges {
                target: self
                color: "#F8D42D"
            }
            PropertyChanges {
                target: locationLabel
                color: "#113B92"
            }
            PropertyChanges {
                target: commentLabel
                color: "#113B92"
            }
            PropertyChanges {
                target: currentUpdateLabel
                color: "#113B92"
            }
            PropertyChanges {
                target: updateTag
                color: "#113B92"
            }
        },
        State {
            name: "Serious"
            PropertyChanges {
                target: self
                color: "#F86C00"
            }
        },
        State {
            name: "Severe"
            PropertyChanges {
                target: self
                color: "#E41F1F"
            }
        }
    ]
}
