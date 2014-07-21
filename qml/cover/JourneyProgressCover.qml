import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0

Item {
    id: self

    property string line: "220"
    property string destination: "Putney"
    property string nextStop: "?"

    Connections {
        target: arrivalsData
        onNextStopChanged: {
            self.nextStop = arrivalsData.getNextStop()
            self.destination = arrivalsData.getCurrentDestination()
            self.line = arrivalsData.getCurrentVehicleLine()
        }
    }

    anchors.fill: parent
    Label {
        id: lineLabel
        text: line
        font.bold: true
        font.pixelSize: Theme.fontSizeLarge
        color: Theme.highlightColor
        horizontalAlignment: Text.AlignHCenter
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium
            left: parent.left
            right: parent.right
        }
    }
    Label {
        id: toLabel
        text: "to"
        horizontalAlignment: Text.AlignHCenter
        anchors {
            top: lineLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.paddingMedium
        }
    }
    Label {
        id: destiationLabel
        text: destination
        color: Theme.highlightColor
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors {
            top: toLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.paddingMedium
        }
    }
    Label {
        id: nextLabel
        text: "Next stop:"
        horizontalAlignment: Text.AlignHCenter
        anchors {
            top: destiationLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.paddingMedium
        }
    }
    Label {
        id: nextStopLabel
        text: nextStop
        color: Theme.highlightColor
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors {
            top: nextLabel.bottom
            left: parent.left
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.paddingMedium
        }
    }
}
