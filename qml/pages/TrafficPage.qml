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
import LondonSailUtilities 1.0

import "../gui"


Page {
    property int fewItems: 6

    id: page
    allowedOrientations: Orientation.All

    property DisruptionModel disruptionModel: trafficData.getDisruptionModel()

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
                    if (!view.count) { busyIndicator.running = true }
                    else {
                        refreshWidget.active = true
                        refreshWidget.title = !trafficData.isDownloading() ? "Parsing" : "Downloading"
                    }

                }
                else {
                    pulley.busy = false
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
                if(!view.count) {
                    progressLabel.text = value + ' bytes'
                }
            }
            onStateChanged: {
                if (trafficData.isParsing() && !trafficData.isDownloading() && !view.count) { progressLabel.text = "Please wait whilst parsing data." }
                else if (!trafficData.isParsing() && !trafficData.isDownloading()) { progressLabel = "" }
            }
        }
    }

    SilicaListView {
        id: view
        anchors.fill: parent
        header: SearchHeader {
            title: "Traffic Disruptions"
            state: ""
            onFilterChanged: { disruptionModel.filter(text) }
        }

        footer: TflNotice { /*state: "invisible"*/ }
        PullDownMenu {
            id: pulley
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
        onCountChanged: {
            if (headerItem && headerItem.state === "") {
                headerItem.state = count ? "searchable" : ""
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
