import QtQuick 2.0
import Sailfish.Silica 1.0


BackgroundItem {
    property alias busNumber: numberLabel.text
    property alias destination: destinationLabel.text
    property int eta: 9999

    anchors {
        left: parent.left
        right: parent.right
    }

    Label {
        id: numberLabel
        text: ""
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: Theme.paddingLarge
        }
    }
    Label {
        id: destinationLabel
        text: ""
        anchors.centerIn: parent
    }
    Label {
        id: etaLabel
        text: (eta < 2) ? "due" : eta + "min"
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            rightMargin: Theme.paddingLarge
        }

    }
}
