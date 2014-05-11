import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias name: nameLabel.text
    property string closure: ""
    property string direction: ""
    radius: 10
    height: nameLabel.paintedHeight + detailsLabel.paintedHeight + 2*Theme.paddingMedium
    anchors {
        left: parent.left
        leftMargin: Theme.paddingLarge
        right: parent.right
        rightMargin: Theme.paddingLarge
    }
    color: "grey"
    Label {
        id: nameLabel
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
        id: detailsLabel
        text: closure + " " + direction
        font.pixelSize: Theme.fontSizeExtraSmall
        anchors {
            top: nameLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }
}
