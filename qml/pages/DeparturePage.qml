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
import QtFeedback 5.0
import harbour.london.sail.utilities 1.0
import "../gui"

//TODO user to be able to set radius
Page {
    id: page
//    property string code: ""
    property string codeBeingDragged: ""
    property string codeSwappedFor: ""
    property int currentDragIndex
    property int currentDelegateIndex
    property StopsModel stopsModel: arrivalsData.getStopsQueryModel()
    allowedOrientations: Orientation.All
    onStatusChanged: {
                if (status === PageStatus.Active) { coverData.reportPage(PageCodes.None) }
    }

    function readInput(input) {
        stopsModel.clearStops()
        var re = /^\d+$/
        if (re.test(input)) {
            pageStack.push(Qt.resolvedUrl("BusStopPage.qml"), {'stopID': input } )
        }
        else {
            arrivalsData.getBusStopsByName(input)
        }
    }

    BusyIndicator {
        id: busyIndicator
        running: !view.count && arrivalsData.isDownloadingListOfStops()
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent
    }

    BusyIndicator {
        id: busyIndicator_2
        running: view.count && arrivalsData.isDownloadingListOfStops()
        size: BusyIndicatorSize.Medium
        anchors {
            left: view.left
            leftMargin: Theme.paddingSmall*5
            top: view.top
            topMargin: Theme.paddingSmall*19
        }
    }

    Connections {
        target: arrivalsData
        onDownloadStateChanged: {
            busyIndicator.running = !view.count && arrivalsData.isDownloadingListOfStops()
            busyIndicator_2.running = view.count && arrivalsData.isDownloadingListOfStops()
        }
    }

    VerticalScrollDecorator {
        flickable: view
    }

    HapticsEffect {
        id: hapticsEffect
        attackIntensity: 0.0
        attackTime: 250
        intensity: 1.0
        duration: 100
        fadeTime: 250
        fadeIntensity: 0.0
    }

    Component {
        id: dragDelegate
        MouseArea {
            id: dragArea
            property bool held: false

            anchors {
                left: parent.left
                right: parent.right
                leftMargin: Theme.paddingLarge
                rightMargin: Theme.paddingLarge
            }
            height: infoWidget.height

            drag.target: held ? infoWidget : undefined
            drag.axis: page.isPortrait ? Drag.YAxis : Drag.XAxis

            onPressAndHold: {
                if (infoWidget.isFavorite) {
                    held = true
                    page.backNavigation = false
                    page.forwardNavigation = false
                    hapticsEffect.start()
                    codeBeingDragged = infoWidget.code
                    console.log("dragging " + infoWidget.name + " " + codeBeingDragged)
                    page.currentDelegateIndex = dragArea.VisualDataModel.itemsIndex
                }
            }
            onReleased: {
                held = false
                page.backNavigation = true
                page.forwardNavigation = true

                stopsModel.move(page.currentDelegateIndex,page.currentDragIndex)
            }
            onClicked: {
                //trying to open with an empty string would cause application to terminate
                if (codeData !== "") {
                    pageStack.push(Qt.resolvedUrl("BusStopPage.qml"), {'stopID' : codeData})
                }
                else {
                    //TODO let user know that there was a problem
                }
            }

            StopInfoWidget {
                id: infoWidget
                name: nameData
                type: typeData
                indicator: stopPointIndicatorData
                towards: towardsData !== "" ? "towards " + towardsData : ""
//                distance: ""
                code: codeData
                rank: rankData
                isDragable: dragArea.held

                Drag.active: dragArea.held
                Drag.source: dragArea
                Drag.hotSpot.x: width / 2
                Drag.hotSpot.y: height / 2

                width: dragArea.width

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                states: State {
                    when: dragArea.held

                    ParentChange { target: infoWidget; parent: root }

                    AnchorChanges {
                        target: infoWidget
                        anchors { horizontalCenter: undefined; verticalCenter: undefined }
                    }
                }

                ListView.onAdd: AddAnimation {
                            target: infoWidget
                }

                ListView.onRemove: RemoveAnimation {
                            target: infoWidget
                }
            }

            DropArea {
                anchors { fill: parent; margins: 10 }

                onEntered: {
                    if (infoWidget.isFavorite) {
                        page.currentDragIndex = dragArea.VisualDataModel.itemsIndex
                        visualModel.items.move(
                                drag.source.VisualDataModel.itemsIndex,
                                dragArea.VisualDataModel.itemsIndex)
                    }
                }
            }
        }
    }

    VisualDataModel {
        id: visualModel
        model: stopsModel
        delegate: dragDelegate
    }

    SilicaListView {
        id: view
        anchors.fill: parent

        header: SearchHeader {
            title: "Bus Departures"
            placeholderText: "Code/Stop Name"
            onEnterClicked: readInput(text)
            state: "visible"
        }

        footer: TflNotice {}
//        PullDownMenu {
//            id: pulley
//            MenuItem {
//                text: "Underground"
//            }
//            MenuItem {
//                text: "Here"
//                enabled: false
//                visible: false
//            }
//        }

        spacing: 10
        model: visualModel

        ViewPlaceholder {
            text: "Enter Bus Stop's name or code."
            enabled: !view.count && !busyIndicator.running
        }
    }

    Component.onDestruction: {
        stopsModel.clearStops()
    }
}
