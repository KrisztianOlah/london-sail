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


BackgroundItem {
    id: self
    property alias busNumber: numberLabel.text
    property alias destination: destinationLabel.text
    property string busId: ""
    property int eta: 9999

    anchors {
        left: parent.left
        right: parent.right
    }

    Label {
        id: numberLabel
        text: ""
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: Theme.paddingLarge
        }
    }
    Label {
        id: destinationLabel
        text: ""
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors {
            verticalCenter: parent.verticalCenter
            left: numberLabel.right
            leftMargin: Theme.paddingMedium
            right: etaLabel.left
            rightMargin: Theme.paddingMedium
        }
    }
    Label {
        id: etaLabel
        text: (eta < 2) ? "due" : eta + "min"
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            rightMargin: Theme.paddingLarge
        }

    }
    Separator {
        anchors {
            top: destinationLabel.bottom
            left: parent.left
            right: parent.right
        }
        color: Theme.highlightColor
    }

    onClicked: {
        arrivalsData.setCurrentVehicleId(busId)
        arrivalsData.setCurrentVehicleLine(busNumber)
        arrivalsData.setCurrentDestination(destination)
        pageStack.push(Qt.resolvedUrl("../pages/JourneyProgressPage.qml"), {'vehicleId' : busId,
                           'lineName' : busNumber, 'destination' : destination } )
    }
}
