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
    property string title: "Title"
    property alias text: searchField.text
    property string placeholderText: "Search"
    property bool readOnly: searchField.readOnly

    signal enterClicked()

    height: header.height + searchField.height + 2 * Theme.paddingLarge
    anchors {
        left: parent.left
        right: parent.right
    }

    Label {
        id: header
        text: title
        font.pixelSize: Theme.fontSizeLarge
        color: Theme.highlightColor
        horizontalAlignment: Text.AlignRight
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium*2
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }

    SearchField {
        id: searchField
        readOnly: true
        opacity: parent.opacity
        anchors {
            top: header.bottom
            topMargin: Theme.paddingMedium*2
            left: parent.left
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.paddingMedium
        }
        placeholderText: self.placeholderText
        inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
        EnterKey.onClicked: {
            searchField.focus = false
            self.enterClicked()
        }
        onClicked: {
            forceActiveFocus()
        }
    }
    states: [
        State {
            name: "invisible"
            PropertyChanges {
                target: searchField
                visible: false
                readOnly: true
            }
        },
        State {
            name: "visible"
            PropertyChanges {
                target: searchField
                visible: true
                readOnly: false
            }
        }

    ]
}

