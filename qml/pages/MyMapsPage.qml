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
import harbour.london.sail.utilities 1.0

import "../gui"

Page {
    id: page
    allowedOrientations: Orientation.All
    //TODO add delete all function and in the pulley
    property FilesModel fileModel: mapData.getMapFilesModel()

    function deleteAllLocalMaps() {
        remorsePopup.execute("Deleting all maps",function () {fileModel.removeAll()})
    }
    NotificationWidget {
        id: notification
        timeOut: 2000
    }

    RemorsePopup { id: remorsePopup }

    SilicaListView {
        id: view
        property Item contextMenu
        property int cIndex: 0
        signal deleteRequested (int index)

        anchors.fill: parent
        header: PageHeader {
            title: "My Bus Maps"
        }

        footer: Item {
            height: Theme.paddingLarge
            width: 1
        }
        PullDownMenu {
            visible: view.count
            MenuItem {
                text: "Delete all maps"
                onClicked: deleteAllLocalMaps()
            }
        }
        ViewPlaceholder {
            enabled: !view.count
            text: "There are no maps downloaded."
        }

        model: fileModel

        delegate: Item {
            id: fileDelegate
            objectName: "fileDelegate"
            property bool menuOpen: view.contextMenu != null && view.contextMenu.parent === fileDelegate

            function deleteFile() {
                remorseItem.execute( fileDelegate, "Deleting",
                                    function () { fileModel.remove(index) } )
            }
            function deleteByIndex(i) {
                if ( i === index ) { deleteFile() }
            }

            height: menuOpen ? backgroundItem.height + view.contextMenu.height : backgroundItem.height
            width: ListView.view.width
            BackgroundItem {
                id: backgroundItem
                height: label.paintedHeight + Theme.paddingMedium * 2 < 80 ? 80 : label.paintedHeight + Theme.paddingMedium * 2
                anchors {
                    left: parent.left
                    right: parent.right
                }
                Separator {
                    color: Theme.secondaryHighlightColor
//                    alignment: Qt.AlignHCenter
                    anchors {
                        top: parent.bottom
                        left: parent.left
                        right: parent.right
                    }
                }

                Label {
                    id: label
                    text: nameData
                    wrapMode: Text.WordWrap
                    textFormat: Text.RichText
                    anchors {
                        left: parent.left
                        right: parent.right
                        leftMargin: Theme.paddingLarge
                        rightMargin: Theme.paddingLarge
                        verticalCenter: parent.verticalCenter
                    }
                }
                RemorseItem { id: remorseItem }
                onClicked: {
                    if (mapData.isThereLocalFile(nameData)) {
                        notification.text = "Opening " + nameData + "..."
                        notification.active = true
                        mapData.openMap(nameData)
                    }
                }
                onPressAndHold: {
                    view.cIndex = index
                    if (!view.contextMenu) {
                        view.contextMenu = contextMenuComponent.createObject(view)
                    }
                    view.contextMenu.show(fileDelegate)
                }
            }

            ListView.onRemove: RemoveAnimation {
                target: fileDelegate
            }
        }

        onDeleteRequested: {
            for (var ix = 0; ix !== view.contentItem.children.length; ++ix) {
                if (view.contentItem.children[ix].objectName === "fileDelegate") {
                    view.contentItem.children[ix].deleteByIndex(index)
                }
            }
        }

        Component {
            id: contextMenuComponent
            ContextMenu {
                MenuItem {
                    text: "delete"
                    onClicked: {
                        view.deleteRequested(view.cIndex)
                    }
                }
            }
        }

        VerticalScrollDecorator {
            flickable: view
        }
    }
    Component.onCompleted: fileModel.reset()
}
