import QtQuick 2.0
import Sailfish.Silica 1.0

import "../gui"
//TODO
//          ---==Remind Me==---//needs busNr(s), Dest, time, ability to skip to next...
//         ---==show on Map==---
Page {
    id: page
    SilicaFlickable {
        anchors.fill: parent
        Column {
            width: page.width
            PageHeader {
                title: "Charing Cross Hospital"
            }
            StopHeader {
                stopSign: "H"
                direction: "Putney Bridge"
                distance: "200m"
            }

            BusWidget {
                busNumber: "220"
                destination: "Wandsworth"
                eta: "2 min"
            }
            BusWidget {
                busNumber: "295"
                destination: "Clapham Junction"
                eta: "4 min"
            }
            BusWidget {
                busNumber: "211"
                destination: "Victoria"
                eta: "8 min"
            }
        }
    }
}
