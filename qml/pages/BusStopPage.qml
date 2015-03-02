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
//TODO
//          ---==Remind Me==---//needs busNr(s), Dest, time, ability to skip to next...
//         ---==show on Map==---

//This page Shows a Bus stop and its data relevant to users such as what buses are supposed to arrive, when and with what destination.
//It also displays any relevant messages from Tfl.
Page {
    id: page
    property string stopID: ""//"74612"//"52727"//"52725"
    property bool isDownloading: false
    allowedOrientations: Orientation.All
    onStatusChanged: {
        if (status === PageStatus.Active) {
            coverData.reportPage(PageCodes.BusStopPage)
        }
    }

    BusyIndicator {
        id: busyIndicator
        running: !view.count && (arrivalsData.isDownloadingArrivals() || arrivalsData.isDownloadingStop())
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent
    }
    Connections {
        target: arrivalsData
        onDownloadStateChanged: {
            busyIndicator.running = !view.count && (arrivalsData.isDownloadingArrivals() || arrivalsData.isDownloadingStop())
            pulley.busy = arrivalsData.isDownloadingArrivals() || arrivalsData.isDownloadingStop()
            refreshMenuItem.enabled = !(arrivalsData.isDownloadingArrivals() || arrivalsData.isDownloadingStop())
        }
    }

    SilicaListView {
        id: view
        property Stop currentStop: arrivalsData.getCurrentStop()
        property string busStopName: ""
        property string stopIndicator: ""
        property string stopCode: ""
        property string direction: ""
        property string distance: ""
        property bool isLoading: true
        property int type: 0

        property ArrivalsModel arrivalsModel: arrivalsData.getArrivalsModel()

        PullDownMenu {
            id: pulley
            MenuItem {
                id: refreshMenuItem
                text: "Refresh"
                onClicked: {
                    arrivalsData.startArrivalsUpdate()
                }
            }
        }

        Connections {
            target: view.currentStop
            onDataChanged: {
                //this will only happen once when the page opens and downloaded the information for the stop
                if (view.currentStop.getType() === Stop.Bus || view.currentStop.getType() === Stop.River) {
                    view.busStopName = view.currentStop.getName()
                    view.stopIndicator = view.currentStop.getStopPointIndicator()
                    view.direction = view.currentStop.getTowards()
                    view.type = view.currentStop.getType()
                    view.stopCode = view.currentStop.getID()
                    arrivalsData.refreshArrivalsModel()

                    //only start updating if header data is already available
                    arrivalsData.startArrivalsUpdate()
                }
            }
        }

        anchors.fill: parent
        model: arrivalsModel
        header: StopHeader {
            currentStop: view.currentStop
            distance: view.distance

            state: "invisible"
        }
        footer: TflNotice {}

        delegate: BusWidget {
            id: busWidget
            busNumber: lineData
            destination: destinationData
            eta: etaData
            busId:  idData
            ListView.onAdd: AddAnimation {
                target: busWidget
            }
            ListView.onRemove: RemoveAnimation {
                target: busWidget
            }
        }
        VerticalScrollDecorator {
            flickable: view
        }
        onCountChanged: {
            if (footerItem) { footerItem.state = count ? "visible" : "invisible" }
        }
        Component.onCompleted: {
            arrivalsData.getBusStopByCode(page.stopID)
            arrivalsData.getBusStopMessage(page.stopID)
        }
        Component.onDestruction: {
            arrivalsData.stopArrivalsUpdate()
            arrivalsData.clearCurrentStop()
            coverData.reportPage(PageCodes.None)
            arrivalsData.setStopsQueryModel(Stop.Bus)
        }
    }
}
