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
    property alias text: searchHeader.text
    property string placeholderText: "Search/Filter"

    signal filterChanged()
    height: searchHeader.height + 2 * Theme.paddingLarge
    anchors {
        left: parent.left
        right: parent.right
    }
    onHeightChanged: console.log("###### Height Changed")
    onXChanged: console.log("##### x Changed")
    onYChanged: console.log("#### y Changed")
    SearchHeader {
        id: searchHeader
        title: self.title
        placeholderText: self.placeholderText
        state: "invisible"

        onTextChanged: filterChanged()
    }

    state: ""

    states: [
        State {
            name: ""
            PropertyChanges {
                target: searchHeader
                state: "invisible"
            }
        },
        State {
            name: "searchable"
            PropertyChanges {
                target: searchHeader
                state: "visible"
            }
        },
        State {
            name: "Traffic Disruptions"
            PropertyChanges {
                target: self
                title: "Traffic Disruptions"
            }
            PropertyChanges {
                target: searchHeader
                state: "visible"
            }
        },
        State {
            name: "Scheduled"
            PropertyChanges {
                target: self
                title: "Scheduled"
            }
            PropertyChanges {
                target: searchHeader
                state: "visible"
            }
        },
        State {
            name: "Recurring Works"
            PropertyChanges {
                target: self
                title: "Recurring Works"
            }
            PropertyChanges {
                target: searchHeader
                state: "visible"
            }
        },
        State {
            name: "Recently Cleared"
            PropertyChanges {
                target: self
                title: "Recently Cleared"
            }
            PropertyChanges {
                target: searchHeader
                state: "visible"
            }
        }
    ]
}
