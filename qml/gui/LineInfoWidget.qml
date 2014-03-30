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


//This is a Widget meant to represent a tube line and
//its related service status information
Rectangle {
    id: self
    property alias labelText: label.text
    property alias text: info.text

    property alias labelColor: label.color
    property alias textColor: info.color

    property color defaultTextColor: "#FFFFFF"
    property int idealHeight: 40 + 20 + (30 * info.lineCount)
    property int visibility: 0
    property string status: ""
    property string details: ""
    //to signal when the last item is reached and clicked
    //when this signal is emitted SilicaFlickable should scroll to the
    //bottom as contentHeight would have changed
    signal itemReached

    function setNormalState() {
        info.text = status
        self.state = "normal"
    }


    height: idealHeight
    radius: 10
    state: "invisible"
    anchors {
        left: parent.left
        right: parent.right
        leftMargin: 50
        rightMargin: 50
    }
    Connections {
        target: serviceStatusData
        onDataChanged: {
            self.status = serviceStatusData.getInfo(labelText)
            self.details = serviceStatusData.getDetails(labelText)
            self.state = "normal"
            infoIcon.state = self.details === "" ? "invisible" : "visible"
        }
    }
    InfoIcon {
        id: infoIcon
        size: 30
        color: parent.color
        labelColor: parent.labelColor
        anchors {
            right: parent.right
            rightMargin: 10
            top: parent.top
            topMargin: 10
        }
    }
    Label {
        id: label
        color: defaultTextColor
        font.family: Theme.fontFamily
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }
    Label {
        id: info
        color: defaultTextColor
        font.family: Theme.fontFamily
        font.pixelSize: Theme.fontSizeExtraSmall
        text: status
        width: parent.width
        wrapMode: Text.WordWrap
        anchors {
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            topMargin: 5
            top: label.bottom
        }
    }

    onTextChanged: {
        self.state = (self.text == "") ? "invisible" : "normal"
    }

    MouseArea {
        id: mousearea
        anchors.fill: parent
        onClicked: {
            if (self.state == "normal" && details != "") {
                for (var i = 0; i !== self.parent.children.length; ++i) {
                    if (self.parent.children[i].objectName === "infoWidget") self.parent.children[i].setNormalState()
                }
                info.text = status + "\n\n" + details
                self.state = "detailed"
            }
            else setNormalState()
        }
    }
    Component.onCompleted: mousearea.clicked.connect(itemReached)

    states: [
        //It is only initial state, after first refresh, or unless whilst being refreshed it shouldn't be active
        State {
            name: "invisible"
            PropertyChanges {
                target: label
                opacity: 0
            }
            PropertyChanges {
                target: info
                opacity: 0
            }
            PropertyChanges {
                target: self
                height: 0
                opacity: 0
                visibility: 0
                anchors.topMargin: 0
            }
        },
        State {
            name: "normal"
            PropertyChanges {
                target: label
                opacity: 100
            }
            PropertyChanges {
                target: info
                opacity: 100
            }
            PropertyChanges {
                target: self
                height: idealHeight
                opacity: 100
                visibility: 1
                anchors.topMargin: 10
            }
        },
        //This one is there to indicate when widget is in detailed view.
        State {
            name: "detailed"

        }
    ]
    Behavior on opacity {
        FadeAnimation {}
    }
}
