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
    property string code: ""//"74612"//"52727"
    onStatusChanged: {
                if (status === PageStatus.Active) { coverData.reportPage(PageCodes.None) }
    }

    function readInput(input) {
        pageStack.push(Qt.resolvedUrl("BusStopPage.qml"), {'stopID': input } )
//        new RegExp()
    }

    SilicaListView {
        id: view
        anchors.fill: parent

        header: Item {
            height: Theme.paddingMedium*6 + pageHeader.height
            anchors {
                left: parent.left
                right: parent.right
            }

            Label {
                id: pageHeader
                text: "Bus Departures"
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

            SearchField {
                id: searchfield
//                validator:
                placeholderText: "Code/Stop Name"
                EnterKey.onClicked: readInput(text)
                anchors {
                    top: pageHeader.bottom
                    topMargin: Theme.paddingMedium*2
                    left: parent.left
                    leftMargin: Theme.paddingMedium
                    right: parent.right
                    rightMargin: Theme.paddingMedium
                }

            }
        }
        footer: TflNotice {}
        PullDownMenu {
            id: pulley
            MenuItem {
                text: "Check Bus Stop by code"
            }
            MenuItem {
                text: "Search bus stop by name"
            }
            MenuItem {
                text: "Here"
                enabled: false
                visible: false
            }
        }

        spacing: 10
        model: 0//10//myModel
        delegate: StopInfoWidget {
//            name: nameData
//            indicator: indicatorData
//            towards: "towards " + towardsData
//            distance: distanceData + "m"
            onClicked: {
                pageStack.push(Qt.resolvedUrl("BusStopPage.qml")) //use codeData to get info on stop/station
            }
        }
        ViewPlaceholder {
            text: "Pull down to enter for Bus Stop's code."
        }
    }
    Component.onCompleted: {
        arrivalsData.getBusStopsByName("Greyhound Road")//DEBUG
    }
}
