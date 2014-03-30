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

        ScrollDecorator { flickable: flick }


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
                objectName: "infoWidget"
                color: "#AE6118"
                labelText: "Bakerloo"
            }
            LineInfoWidget {
                id: central
                objectName: "infoWidget"
                color: "#E41F1F"
                labelText: "Central"
            }
            LineInfoWidget {
                id: circle
                objectName: "infoWidget"
                color: "#F8D42D"
                labelText: "Circle"
                textColor: "#113B92"
                labelColor: "#113B92"
            }
            LineInfoWidget {
                id: district
                objectName: "infoWidget"
                color: "#007229"
                labelText: "District"
            }
            LineInfoWidget {
                id: dlr
                objectName: "infoWidget"
                color: "#00BBB4"
                labelText: "DLR"
            }
            LineInfoWidget {
                id: hammersmith
                objectName: "infoWidget"
                color: "#E899A8"
                labelText: "Hammersmith and City"
                textColor: "#113B92"
                labelColor: "#113B92"
            }
            LineInfoWidget {
                id: jubilee
                objectName: "infoWidget"
                color: "#686E72"
                labelText: "Jubilee"
            }
            LineInfoWidget {
                id: metropolitan
                objectName: "infoWidget"
                color: "#893267"
                labelText: "Metropolitan"
            }
            LineInfoWidget {
                id: northern
                objectName: "infoWidget"
                color: "#000000"
                labelText: "Northern"
            }
            LineInfoWidget {
                id: overground
                objectName: "infoWidget"
                color: "#F86C00"
                labelText: "Overground"
            }
            LineInfoWidget {
                id: piccadilly
                objectName: "infoWidget"
                color: "#0450A1"
                labelText: "Piccadilly"
            }
            LineInfoWidget {
                id: victoria
                objectName: "infoWidget"
                color: "#009FE0"
                labelText: "Victoria"
            }
            LineInfoWidget {
                id: waterloo
                objectName: "infoWidget"
                color: "#70C3CE"
                labelText: "Waterloo and City"
                textColor: "#113B92"
                labelColor: "#113B92"
                //need to scroll to bottom when widget is in a detailed view
                //otherwise user has to do it which would be annoying
                onItemReached: flick.scrollToBottom()
            }
        }
    }
}
