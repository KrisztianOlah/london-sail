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

import "../gui"
//This page displays the status of all tube/dlr/overground lines and displays if there are any disruptions

Page {
    property int marginCorrection: 250

    id: page
    allowedOrientations: Orientation.All
    onStatusChanged: {
        if (status === PageStatus.Active) {
            pageStack.pushAttached(Qt.resolvedUrl("ThisWeekPage.qml"))
        }
        else if (status === PageStatus.Inactive) { flick.scrollToTop() }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: serviceStatusData.isDownloading()
        size: BusyIndicatorSize.Large

        Connections {
            target: serviceStatusData
            onStateChanged: {
                busyIndicator.running = serviceStatusData.isDownloading()
            }
        }
    }

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: {
                    //removes all widgets until there is fresh data to display
                    for (var i = 0; i !== column.children.length; ++i) {
                        if (column.children[i].objectName === "infoWidget") {} column.children[i].state = "invisible"
                    }
                    serviceStatusData.refresh()
                }
            }
        }

        contentHeight: bakerloo.height + central.height + circle.height + district.height + dlr.height + hammersmith.height +
                       jubilee.height + metropolitan.height + northern.height + overground.height + piccadilly.height +
                       victoria.height + waterloo.height + marginCorrection + Theme.paddingLarge

        VerticalScrollDecorator { flickable: flick }


        Column {
            id: column
            width: page.width
            spacing: 10
            ViewPlaceholder {
                enabled: (!(bakerloo.visibility + central.visibility + circle.visibility + district.visibility + dlr.visibility + hammersmith.visibility +
                         jubilee.visibility + metropolitan.visibility + northern.visibility + overground.visibility + piccadilly.visibility +
                         victoria.visibility + waterloo.visibility) && !busyIndicator.running)
                text: "Pull down to refresh."
            }
            Component.onCompleted: serviceStatusData.refresh()


            PageHeader {
                title: "Service Status"
            }
            //TODO move the colours to a different module to be called from to improve readability just like Theme.highlightColor
            LineInfoWidget {
                id: bakerloo
                color: "#AE6118"
                name: "Bakerloo"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: central
                color: "#E41F1F"
                name: "Central"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: circle
                color: "#F8D42D"
                name: "Circle"
                textColor: "#113B92"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: district
                color: "#007229"
                name: "District"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: dlr
                color: "#00BBB4"
                name: "DLR"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: hammersmith
                color: "#E899A8"
                name: "Hammersmith and City"
                textColor: "#113B92"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: jubilee
                color: "#686E72"
                name: "Jubilee"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: metropolitan
                color: "#893267"
                name: "Metropolitan"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: northern
                color: "#000000"
                name: "Northern"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: overground
                color: "#F86C00"
                name: "Overground"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: piccadilly
                color: "#0450A1"
                name: "Piccadilly"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: victoria
                color: "#009FE0"
                name: "Victoria"
                isServiceStatus: true
            }
            LineInfoWidget {
                id: waterloo
                color: "#70C3CE"
                name: "Waterloo and City"
                textColor: "#113B92"
                isServiceStatus: true
                //need to scroll to bottom when widget is in a detailed view
                //otherwise user has to do it which would be annoying
                onItemReached: flick.scrollToBottom()
            }
        }
    }
}
