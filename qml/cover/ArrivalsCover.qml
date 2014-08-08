import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0
import "../gui"

Item {
    property bool active: false
    property ArrivalsModel arrivalsModel: arrivalsData.getArrivalsModel()
    anchors.fill: parent

    ListView {
        id: view
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium
            bottom: parent.bottom
            left: parent.left
            leftMargin: 40
            right: parent.right
            rightMargin: 40
        }
        model: arrivalsModel
        delegate: Item {
            anchors {
                left: parent.left
                right: parent.right
            }
            height: lineLabel.paintedHeight

            Label {
                id: lineLabel
                text: lineData
                color: Theme.highlightColor
                anchors.left: parent.left
            }
            Label {
                id: etaLabel
                text: etaData < 2 ? "due" : etaData + "min"
                horizontalAlignment: Text.AlignRight
                anchors.right: parent.right
            }
        }
    }
//    onActiveChanged: {
//        if (!active) {
//            v
//        }
//    }

//    Label {
//        anchors.centerIn: parent
//        text: active ? "I'm active!" : "I'm sleeping"
//        RotationAnimation on rotation {
//            running: active
//            duration: 1000
//            loops: Animation.Infinite
//            from: 0; to: 360
//        }
//    }
}
