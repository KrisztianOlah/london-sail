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

//TODO user to be able to set radius
Page {
    id: page
    property string code: ""
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
        onDownloadSatateChanged: {
            busyIndicator.running = !view.count && arrivalsData.isDownloadingListOfStops()
            busyIndicator_2.running = view.count && arrivalsData.isDownloadingListOfStops()
        }
    }

    VerticalScrollDecorator {
        flickable: view
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
        model: arrivalsData.getStopsQueryModel()
        delegate: StopInfoWidget {
            id: infoWidget
            name: nameData
            type: typeData
            indicator: stopPointIndicatorData
            towards: towardsData !== "" ? "towards " + towardsData : ""
            distance: ""
            code: codeData
            onClicked: {
                //trying to open with an empty string would cause application to terminate
                if (codeData !== "") {
                    pageStack.push(Qt.resolvedUrl("BusStopPage.qml"), {'stopID' : codeData})
                }
                else {
                    //TODO let user know that there was a problem
                }
            }
            ListView.onAdd: AddAnimation {
                        target: infoWidget
            }
            ListView.onRemove: RemoveAnimation {
                        target: infoWidget
            }
        }
        ViewPlaceholder {
            text: "Pull down to enter for Bus Stop's code."
        }
    }

    Component.onDestruction: {
        stopsModel.clearStops()
    }
}
