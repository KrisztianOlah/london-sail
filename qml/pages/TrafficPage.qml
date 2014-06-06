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
    property int fewItems: 6

    id: page
    allowedOrientations: Orientation.All

    property DisruptionModel disruptionModel: trafficData.getDisruptionModel()
    property string currentModel: "Traffic Disruptions"

    Component.onCompleted: trafficData.refresh()

    BusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        running: (trafficData.isDownloading() || trafficData.isParsing() )
        anchors.centerIn: parent

        Connections {
            target: trafficData
            onStateChanged: {
                if (trafficData.isDownloading() || trafficData.isParsing()) {
                    pulley.busy = true
                    refreshButton.enabled = false
                    //BUG if view.count is 0 and user refreshes SearchField will not be visible
                    if (!view.count && disruptionModel.isFilterEmptyString() ) {
                        busyIndicator.running = true
                        pulley.enabled = false
                    }
                    else {
                        refreshWidget.active = true
                        refreshWidget.title = !trafficData.isDownloading() ? "Parsing" : "Downloading"
                    }

                }
                else {
                    pulley.busy = false
                    pulley.enabled = true
                    refreshButton.enabled = true
                    busyIndicator.running = false
                    refreshWidget.active = false
                    progressLabel.text = ""
                }
            }
        }
    }

    Label {
        id: progressLabel
        text: ""
        anchors.centerIn: parent

        Connections {
            target: trafficData
            onDownloadProgress: {
                if(!view.count && disruptionModel.isFilterEmptyString()) {
                    progressLabel.text = value + ' bytes'
                }
            }
            onStateChanged: {
                if (trafficData.isParsing() && !trafficData.isDownloading()
                        && !view.count && disruptionModel.isFilterEmptyString()) {
                    progressLabel.text = "Please wait whilst parsing data."
                }
                else if (!trafficData.isParsing() && !trafficData.isDownloading()) {
                    progressLabel = ""
                    //have to clear filter because SearchField in header gets cleared causing a bug
                    disruptionModel.filter("")
                    //setModel(currentModel)
                }

            }
        }
    }
    function setModel(str) {
        currentModel = str
        view.headerItem.state = str
//        Qt.conslole.log("Setting " + str + " as header.")
        disruptionModel.setStatusFilter(str)
    }

    SilicaListView {
        id: view
        anchors.fill: parent
        header: SearchHeader {
            title: currentModel//"Traffic Disruptions"
            state: ""
            onFilterChanged: { disruptionModel.filter(text) }
        }


        footer: TflNotice {}
        PullDownMenu {
            id: pulley
            MenuItem {
                text: "Recently Cleared"
                enabled: text !== currentModel
                visible: text !== currentModel
                onClicked: setModel(text)
            }
            MenuItem {
                text: "Recurring Works"
                enabled: text !== currentModel
                visible: text !== currentModel
                onClicked: setModel(text)
            }
            MenuItem {
                text: "Scheduled"
                enabled: text !== currentModel
                visible: text !== currentModel
                onClicked: setModel(text)
            }
            MenuItem {
                text: "Traffic Disruptions"
                enabled: text !== currentModel
                visible: text !== currentModel
                onClicked: setModel(text)
            }
            MenuItem {
                id: refreshButton
                text: "Refresh"
                onClicked: trafficData.refresh()
            }
        }
        PushUpMenu {
            id: pushy
            enabled: view.count > fewItems
            visible: view.count > fewItems

            MenuItem {
                text: "Go to top"
                onClicked: view.scrollToTop()
            }
        }

        currentIndex: -1
        model: disruptionModel
        spacing: 10
        delegate: RoadDisruptionWidget {
            location: locationData
            comment: commentsData
            currentUpdate: currentUpdateData
            severity: severityData
            disruptionID: idData

        }
//        if "" and count and refresh OK
//        if "dfghjk" !count and refresh OK, but headerItem.cleared() filter is still set
        onCountChanged: {
            if (headerItem && headerItem.state === "") {
                headerItem.state = count || !disruptionModel.isFilterEmptyString() ? "searchable" : ""
            }
            if (footerItem) {
                footerItem.state = count ? "visible" : "invisible"
            }
            // push up menu seems to be pointless when only a handful of items to display
            pushy.enabled = view.count > fewItems
            pushy.visible =  view.count > fewItems
        }

        VerticalScrollDecorator { flickable: view }

        ViewPlaceholder {
            id: placeholder
            enabled: (!busyIndicator.running && !view.count)
            text: (view.headerItem.state === "") ? "Pull down to refresh." : "No matches :("
        }
    }
    RefreshWidget {
        id: refreshWidget
    }
    onOrientationChanged: {
        //BUG: its seems to be reverted for some reason
        refreshWidget.isPortrait = !isPortrait
    }
    //in case user closes page with a filter set
    Component.onDestruction: { disruptionModel.filter("") }
}
