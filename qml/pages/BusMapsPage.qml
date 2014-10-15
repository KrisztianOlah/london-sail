import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0

import "../gui"

Page {
    property string headertitle: ""
    id: page
    allowedOrientations: Orientation.All

    NotificationWidget {
        id: notification
        timeOut: 2000
    }

    SilicaListView {
        id: view
        property string currentName: ""
        property string currentLink: ""
        property int cIndex: 0
        signal deleteRequested (int index)

        anchors.fill: parent
        model: mapData.getMapsModel()
        header: PageHeader {
            title: headertitle
        }
        footer: Item {
            height: Theme.paddingLarge
            width: 1
        }

        delegate: Item {
            id: itemDelegate
            objectName: "mapDelegate"

            width: ListView.view.width
            height: loader.height + contentItem.height

            function refreshItem() {
                loader.item.isLocalFile = mapData.isThereLocalFile(nameData)
                label.color = mapData.isThereLocalFile(nameData) ?
                                               Theme.primaryColor : Theme.secondaryColor }
            function deleteMap() {
                remorseItem.execute( itemDelegate ,"Deleting",
                                    function () { mapData.deleteMap(nameData)} )
            }

            function deleteMapByIndex (ix) {
                if (ix === index) { deleteMap() }
            }

            BackgroundItem {
                id: contentItem

                width: parent.width
                height: label.paintedHeight + Theme.paddingMedium * 2 < 80 ? 80 : label.paintedHeight + Theme.paddingMedium * 2

                Separator {
                    color: Theme.secondaryHighlightColor
                    anchors {
                        top: parent.bottom
                        left: parent.left
                        right: parent.right
                    }
                }

                Label {
                    id: label
                    text: nameData
                    color: mapData.isThereLocalFile(nameData) ? Theme.primaryColor : Theme.secondaryColor
                    wrapMode: Text.WordWrap
                    textFormat: Text.RichText
                    anchors {
                        left: parent.left
                        leftMargin: Theme.paddingLarge
                        right: parent.right
                        rightMargin: Theme.paddingLarge
                        verticalCenter: parent.verticalCenter
                    }
                }
                Connections {
                    target: mapData
                    onMapDownloaded: {
                        refreshItem()
                    }
                    onMapDeleted: {
                        refreshItem()
                    }
                }
                Loader {
                    id: loader
                    sourceComponent: contextMenuComponent
                    height: children.height
                    anchors {
                        left: parent.left
                        right: parent.right
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
                    view.currentName = nameData
                    view.currentLink = linkData
                    view.cIndex = index
                    loader.item.show(itemDelegate)
                }
            }
        }

        Component {
            id: contextMenuComponent
            ContextMenu {
                id: contextMenu
                property bool isLocalFile: mapData.isThereLocalFile(view.currentName)


                MenuItem {
                    text: contextMenu.isLocalFile ? "delete" : "download"
                    onClicked: {
                        if (contextMenu.isLocalFile) {
                            view.deleteRequested(view.cIndex)
                        }
                        else {
                            mapData.downloadMap(view.currentName, view.currentLink)
                        }
                    }
                }
            }
        }
        VerticalScrollDecorator {
            flickable: view
        }
        onDeleteRequested: {
            for (var i = 0; i !== view.contentItem.children.length; ++i) {
                if (view.contentItem.children[i].objectName === "mapDelegate") {
                    view.contentItem.children[i].deleteMapByIndex(index)
                }
            }
        }
    }
    Connections {
        target: mapData
        onDownloadingChanged: {
            refreshWidget.active = mapData.isDownloading()
        }
    }

    RefreshWidget {
        id: refreshWidget
        title: "Downloading"
    }
    onOrientationChanged: {
        //BUG: its seems to be reverted for some reason
        refreshWidget.isPortrait = !isPortrait
    }

    Component.onCompleted: { mapData.downloadListOfMapsFor(headertitle) }
    Component.onDestruction: { mapData.clearMapList()}
}
