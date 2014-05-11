import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: self
    property string title: "Title"
    property alias text: searchField.text

    signal filterChanged()
    height: header.height + searchField.height + 2*Theme.paddingLarge
    anchors {
        left: parent.left
        right: parent.right
    }
    state: ""
    Label {
        id: header
        text: title
        font.pixelSize: Theme.fontSizeLarge
        color: Theme.highlightColor
        anchors {
            top: parent.top
            topMargin: Theme.paddingMedium*2
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
    }
    SearchField {
        id: searchField
        width: 480
        opacity: 0
        readOnly: true
        anchors {
            top: header.bottom
            left: parent.left
            leftMargin: Theme.paddingLarge
        }
        placeholderText: "Search/Filter"
        inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
        EnterKey.onClicked: {
            searchField.focus = false
        }
        onClicked: {
            forceActiveFocus()
        }

        onTextChanged: {
            self.filterChanged()
        }
    }
    states: [
        State {
            name: ""
            PropertyChanges {
                target: searchField
                opacity: 0
                readOnly: true
            }
        },
        State {
            name: "searchable"
            PropertyChanges {
                target: searchField
                opacity: 100
                readOnly: false
            }
        }

    ]
}
