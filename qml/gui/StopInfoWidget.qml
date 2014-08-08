import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0

Rectangle {
    property alias distance: distanceLabel.text
    property alias name: nameLabel.text
    property int type: 0
    property string indicator: ""
    property string towards: ""
    property string code: ""
    property bool isFavorite: arrivalsData.isStopFavorite(code)
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
        id: stopIcon
        height: 60
        width: height
        radius: height/2
        color: (type === Stop.Bus) ? "red" : "blue"
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
    }
    Label {
        id: indicatorLabel
        text: indicator
        anchors.centerIn: stopIcon
        font.bold: true
    }

    Label {
        id: nameLabel
        text: "Name of Stop"
        font.pixelSize: Theme.fontSizeMedium
        anchors {
            top: parent.top
            topMargin: (towards === "") ? 30 : 10 //no need to leave space when there is nothing to display
            left: stopIcon.right
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
            left: stopIcon.right
            leftMargin: Theme.paddingMedium
            right: iconButton.left
            rightMargin: Theme.paddingMedium
        }
    }

    Label {
        id: distanceLabel
        text: "distance"
        font.pixelSize: Theme.fontSizeExtraSmall
        anchors {
            top: stopIcon.bottom
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
