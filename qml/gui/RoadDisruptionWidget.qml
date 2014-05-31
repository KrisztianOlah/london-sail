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
    id: self
    property alias location: locationLabel.text
    property string comment: ""
    property string currentUpdate: ""
    property string severity: "Minimal"
    property int disruptionID: 0

    height: (locationLabel.paintedHeight < 150) ? 150 : (locationLabel.paintedHeight + 2*Theme.paddingMedium)
    radius: 10
    anchors {
        left: parent.left
        leftMargin: Theme.paddingLarge
        right: parent.right
        rightMargin: Theme.paddingLarge
    }
    MouseArea {
        id: mousearea
        anchors.fill: parent
        onClicked: pageStack.push(Qt.resolvedUrl("../pages/TrafficDetailsPage.qml"),
                                  {'location': self.location, 'comment': self.comment,
                                      'currentUpdate': self.currentUpdate, 'severity': self.severity,
                                      'disruptionID' : self.disruptionID})
    }

    state: severity
    Label {
        id: locationLabel
        text: "Location"
        font.bold: true
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
    }
    //These states are only used when RoadDisruptionWidgets are created,
    //they aren't changing dynamically
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


