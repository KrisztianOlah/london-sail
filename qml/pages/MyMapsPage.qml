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
        signal deleteRequested (int index)

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
