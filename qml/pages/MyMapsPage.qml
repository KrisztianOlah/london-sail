import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0

Page {
    id: page
    allowedOrientations: Orientation.All
    //TODO add delete all function and in the pulley
    property FilesModel fileModel: mapData.getMapFilesModel()
    SilicaListView {
        id: view
        property Item contextMenu
        property int cIndex: 0

        anchors.fill: parent
        header: PageHeader {
            title: "My Bus Maps"
        }
        footer: Item {
            height: Theme.paddingLarge
            width: 1
        }

        model: fileModel
        delegate: Item {
            id: fileDelegate
            property bool menuOpen: view.contextMenu != null && view.contextMenu.parent === fileDelegate

            function deleteFile() {
                remorseItem.execute( fileDelegate, "Deleting",
                                    function () { fileModel.remove(index) } )
            }

            height: menuOpen ? backgroundItem.height + view.contextMenu.height : backgroundItem.height
            width: ListView.view.width
            BackgroundItem {
                id: backgroundItem
                anchors {
                    left: parent.left
                    right: parent.right
                }
                Label {
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


        Component {
            id: contextMenuComponent
            ContextMenu {
                MenuItem {
                    text: "delete"
                    onClicked: {
                        // +2 because header and footer are also children
                        view.contentItem.children[view.cIndex + 2].deleteFile()
                    }
                }
            }
        }

        VerticalScrollDecorator {
            flickable: view
        }
    }
}
