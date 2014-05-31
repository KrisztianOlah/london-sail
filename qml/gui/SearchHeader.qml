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

    signal filterChanged()
    height: header.height + searchField.height + 2*Theme.paddingLarge
    anchors {
        left: parent.left
        right: parent.right
    }
    state: ""
    Label {
        id: header
        text: title
        font.pixelSize: Theme.fontSizeLarge
        color: Theme.highlightColor
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium*2
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }
    SearchField {
        id: searchField
        width: 480
        opacity: 0
        readOnly: true
        anchors {
            top: header.bottom
            left: parent.left
            leftMargin: Theme.paddingLarge
        }
        placeholderText: "Search/Filter"
        inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
        EnterKey.onClicked: {
            searchField.focus = false
        }
        onClicked: {
            forceActiveFocus()
        }

        onTextChanged: {
            self.filterChanged()
        }
    }
    states: [
        State {
            name: ""
            PropertyChanges {
                target: searchField
                opacity: 0
                readOnly: true
            }
        },
        State {
            name: "searchable"
            PropertyChanges {
                target: searchField
                opacity: 100
                readOnly: false
            }
        }

    ]
}
