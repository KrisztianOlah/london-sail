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


Page {
    id: page
    property string vehicleId: ""
    property string headerTitle: vehicleId
    property string lineName: "lineName"
    property string destination: "dest"
    property ArrivalsModel progressModel: arrivalsData.getJourneyProgressModel()

    allowedOrientations: Orientation.All

    onStatusChanged: {
        if (status === PageStatus.Active) { coverData.reportPage(PageCodes.JourneyProgressPage) }
    }

    function whatColor(exact) {
        if (exact > -10000 && exact < 20000) return Theme.highlightColor
        if (exact > -10000) return Theme.primaryColor
        else return Theme.secondaryColor
    }

    function resetSmallest() {
        smallest = 30000
    }
    Connections {
        target: progressModel
        onDataChanged: {
            resetSmallest()
        }
    }

    SilicaListView {
        id: view
        anchors.fill: parent
        header: Item {
            height: Theme.paddingMedium*6 + pageHeader.height + destinationLabel.paintedHeight
            anchors {
                left: parent.left
                right: parent.right
            }

            Label {
                id: pageHeader
                text: headerTitle
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeLarge
                horizontalAlignment: Text.AlignRight
                anchors {
                    top: parent.top
                    topMargin: Theme.paddingMedium*2
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
            }
            Label {
                id: lineNameLabel
                text: lineName
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
                font.bold: true
                anchors {
                    top: pageHeader.bottom
                    topMargin: Theme.paddingMedium*2
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                }
            }
            Label {
                id: destinationLabel
                text: "to " + destination
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeLarge
                anchors {
                    top: pageHeader.bottom
                    topMargin: Theme.paddingMedium*2
                    left: lineNameLabel.right
                    leftMargin: Theme.paddingMedium
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }

            }
        }
        footer: TflNotice {}

        model: progressModel
        displaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 1000 }
            }
        delegate: Item {
            height: stopLabel.paintedHeight + Theme.paddingSmall*2

            anchors {
                left: parent.left
                right: parent.right
            }
            Rectangle {
                anchors.fill: parent
                color: Theme.secondaryHighlightColor
                opacity: index % 2 ? 0 : 100
            }
            Label {
                id: etaLabel
                text: sortData > -10000 ? etaData + "min": ""
                color: whatColor(sortData)
                anchors {
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                    verticalCenter: parent.verticalCenter
                }
            }
            Label {
                id: stopLabel
                text: stopNameData
                color: whatColor(sortData)
                font.bold: sortData > -10000 && sortData < 20000
                wrapMode: Text.WordWrap
                anchors {
                    top: parent.top
                    topMargin: Theme.paddingSmall
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: etaLabel.left
                    rightMargin: Theme.paddingExtraLarge
                }
            }
        }
        VerticalScrollDecorator {
            flickable: view
        }

        onCountChanged: {
            if (footerItem) { footerItem.state = count ? "visible" : "invisible" }
        }

    }

    Component.onCompleted: {
        arrivalsData.stopArrivalsUpdate()
        arrivalsData.startJourneyProgressUpdate()
    }

    Component.onDestruction: {
        arrivalsData.stopJourneyProgressUpdate()
        arrivalsData.startArrivalsUpdate()
    }
}
