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

//get stop type using "StopPointType", "SLRS" = river


//Millbank pier for Tate Britain
//Bankside Pier for Tate Modern
//London Bridge Pier for London Bridge and the Shard
//Tower Pier for Tower of London and Tower Bridge
//Hilton London Docklands Riverside Pier
//North Greenwich Pier for The O2
//Greenwich Pier for Greenwich

Page {
    id: page
    property string stopID: ""//"74612"//"52727"//"52725"
    allowedOrientations: Orientation.All
    onStatusChanged: {
        if (status === PageStatus.Active) {
            coverData.reportPage(PageCodes.BusStopPage)
        }
    }
//    bool isDownloadingArrivals() const;
//    bool isDownloadingJourneyProgress() const;
//    bool isDownloadingListOfStops() const;
//    bool isDownloadingStop() const;
//    function isBusy() {
//        //
//    }

    BusyIndicator {
        id: busyIndicator
        running: !view.count && (arrivalsData.isDownloadingArrivals() || arrivalsData.isDownloadingStop())
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent
    }
    Connections {
        target: arrivalsData
        onDownloadSatateChanged: {
            busyIndicator.running = !view.count && (arrivalsData.isDownloadingJourneyProgress() || arrivalsData.isDownloadingStop())
        }
    }

    SilicaListView {
        id: view
        property Stop currentStop: arrivalsData.getCurrentStop()
        property string busStopName: ""
        property string stopIndicator: ""
        property string direction: ""
        property string distance: ""
        property bool isLoading: true
        property int type: 0

        property ArrivalsModel arrivalsModel: arrivalsData.getArrivalsModel()

        Connections {
            target: view.currentStop
            onDataChanged: {
                //this will only happen once when the page opens and downloaded the information for the stop
                if (view.currentStop.getType() === Stop.Bus || view.currentStop.getType() === Stop.River) {
                    view.busStopName = view.currentStop.getName()
                    view.stopIndicator = view.currentStop.getStopPointIndicator()
                    view.direction = view.currentStop.getTowards()
                    view.type = view.currentStop.getType()

                    //only start updating if header data is already available
                    arrivalsData.startArrivalsUpdate()
                }
            }
        }

        anchors.fill: parent
        model: arrivalsModel
        header: StopHeader {
            title: view.busStopName
            stopIndicator: view.stopIndicator
            direction: view.direction
            distance: view.distance
            type: view.type
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
        }
        Component.onDestruction: {
            arrivalsData.stopArrivalsUpdate()
            arrivalsData.clearCurrentStop()
            coverData.reportPage(PageCodes.None)
        }
    }
}
