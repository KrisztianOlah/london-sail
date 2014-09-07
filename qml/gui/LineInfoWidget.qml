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
    objectName: "infoWidget"
    property alias name: label.text
    property alias statusText: statusLabel.text

    property alias iconColor: icon.iconColor

    property color textColor: "#FFFFFF"
    property int idealHeight: 40 + 20 + statusLabel.paintedHeight
    property int detailedHeight: idealHeight + detailLabel.paintedHeight
    property int visibility: 0
    property string status: ""
    property string details: ""
    //use this as a temporary Solution for bug where user refreshes "Status Updates"
    //and it overwrites "This Weekend" as well!
    property bool isServiceStatus: false
    //to signal when the last item is reached and clicked
    //when this signal is emitted SilicaFlickable should scroll to the
    //bottom as contentHeight would have changed
    signal clicked

    function setNormalState() {
        self.state = "normal"
        icon.state = self.details === "" ? "invisible" : "visible"
    }

    function setDetailedState() {
        self.state = "detailed"
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
    //BUG this bit causes a bug where user refreshes "Status Updates" and it overwrites
    //"This Weekend" as well!
    Connections {
        target: serviceStatusData
        onDataChanged: {
            //the if statement is a temporary fix for the aformentioned bug, in a long term it should be fixed
            //by using mvc like ThisWeekPage when this connections can be removed altogether
            if (isServiceStatus) {
                self.status = serviceStatusData.getInfo(name)
                self.details = serviceStatusData.getDetails(name)
                setNormalState()
            }
        }
    }

    InfoIcon {
        id: icon
        size: 30
        color: parent.color
        iconColor: parent.textColor
        state: self.details === "" ? "invisible" : "visible"
        anchors {
            right: parent.right
            rightMargin: 10
            top: parent.top
            topMargin: 10
        }
    }

    Label {
        id: label
        color: textColor
        font.family: Theme.fontFamily
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }

    Label {
        id: statusLabel
        color: textColor
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
    Label {
        id: detailLabel
        clip: true
        truncationMode: TruncationMode.Fade
        color: textColor
        font.pixelSize: Theme.fontSizeExtraSmall
        text: details
        opacity: 0
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        anchors {
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            topMargin: 5
            top: statusLabel.bottom
            bottom: self.bottom
        }
    }

    onStatusTextChanged: {
        self.state = (self.text === "") ? "invisible" : "normal"
    }

    MouseArea {
        id: mousearea
        anchors.fill: parent
        onClicked: {
            if (self.state == "normal" && details != "") {
                //reset the size/state of siblings
                for (var i = 0; i !== self.parent.children.length; ++i) {
                    if (self.parent.children[i].objectName === "infoWidget") self.parent.children[i].setNormalState()
                }
                setDetailedState()
            }
            else setNormalState()
        }
    }
    Component.onCompleted: mousearea.clicked.connect(clicked)

    states: [
        //It is only initial state, after first refresh, or unless whilst being refreshed it shouldn't be active
        State {
            name: "invisible"
            PropertyChanges {
                target: label
                opacity: 0
            }
            PropertyChanges {
                target: statusLabel
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
                target: statusLabel
                opacity: 100
            }
            PropertyChanges {
                target: detailLabel
                opacity: 0
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
            PropertyChanges {
                target: self
                height: detailedHeight
            }
            PropertyChanges {
                target: detailLabel
                opacity: 100
            }

        }
    ]
    Behavior on opacity {
        FadeAnimation {}
    }
    transitions: [
        Transition {
            from: "normal"
            to: "detailed"
            NumberAnimation { target: self; property: "height" ; duration: (detailedHeight - idealHeight) * 2 }
            NumberAnimation {
                target: detailLabel;
                property: "opacity";
                duration: (detailedHeight - idealHeight) * 2;
                easing.type: Easing.InQuint
            }
        },
        Transition {
            from: "detailed"
            to: "normal"
            NumberAnimation { target: self; property: "height" ; duration: (detailedHeight - idealHeight) * 2 }
            NumberAnimation {
                target: detailLabel;
                property: "opacity";
                duration: (detailedHeight - idealHeight) * 2;
                easing.type: Easing.OutQuint
            }
        }
    ]
}
