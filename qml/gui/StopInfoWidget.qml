import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias distance: distanceLabel.text
    property alias name: nameLabel.text
    property string indicator: ""
    property string towards: ""
    signal clicked

    id: self
    height: 80 + towardLabel.lineCount * 20
    radius: 10
    color: Theme.secondaryHighlightColor
    anchors {
        left: parent.left
        right: parent.right
        leftMargin: Theme.paddingLarge
        rightMargin: Theme.paddingLarge
    }
    MouseArea {
        id: mousearea
        anchors.fill: parent
    }
    Component.onCompleted: mousearea.clicked.connect(clicked)

    Rectangle {
        id: icon
        height: 60
        width: height
        radius: height/2
        color: "red"
        anchors {
            left: parent.left
            leftMargin: 10
            top: parent.top
            topMargin: 12
        }
    }
    Label {
        id: indicatorLabel
        text: indicator
        anchors.centerIn: icon
        font.bold: true
    }

    Label {
        id: nameLabel
        text: "Name of Stop"
        font.pixelSize: Theme.fontSizeMedium
        anchors {
            top: parent.top
            topMargin: (towards === "") ? 30 : 10 //no need to leave space when there is nothing to display
            left: icon.right
            leftMargin: icon.width + 10

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
            leftMargin: icon.width + 10
            right: parent.right
        }
    }

    Label {
        id: distanceLabel
        text: "distance"
        font.pixelSize: Theme.fontSizeExtraSmall
        anchors {
            top: icon.bottom
//            topMargin: 2//Theme.fontSizeLarge
            left: parent.left
            leftMargin: 10
        }
    }
}
