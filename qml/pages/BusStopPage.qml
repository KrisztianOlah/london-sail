import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.london.sail.utilities 1.0
import "../gui"
//TODO
//          ---==Remind Me==---//needs busNr(s), Dest, time, ability to skip to next...
//         ---==show on Map==---

Page {
    id: page
    SilicaListView {
        id: view

        property Stop currentStop: arrivalsData.getCurrentStop()
        property string busStopName: ""
        property string stopIndicator: ""
        property string direction: ""
        property string distance: ""
        property string stopID: "52727"//"74612"
        property bool loadingHeader: true
        property ArrivalsModel arrivalsModel: arrivalsData.getArrivalsModel()

        Connections {
            target: view.currentStop
            onDataChanged: {
                //this will only happen once when the page opens and downloaded the information for the stop
                if (view.currentStop.getType() === Stop.Bus ) {
                    view.busStopName = view.currentStop.getName()
                    view.stopIndicator = view.currentStop.getStopPointIndicator()
                    view.direction = view.currentStop.getTowards()

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
            isBusStop: true
        }

        delegate: BusWidget {
            busNumber: lineData
            destination: destinationData
            eta: etaData
//            "idData";//vehicle id
        }
        Component.onCompleted: {
            arrivalsData.getBusStopByCode(view.stopID)
        }
        Component.onDestruction: {
            arrivalsData.stopArrivalsUpdate()
            arrivalsData.clearCurrentStop()
        }

        onLoadingHeaderChanged: {

            if (!loadingHeader) {}
        }
    }
}
