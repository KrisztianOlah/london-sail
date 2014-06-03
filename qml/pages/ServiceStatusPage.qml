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
    id: page
    allowedOrientations: Orientation.All
    onStatusChanged: {
        if (status === PageStatus.Active) {
            pageStack.pushAttached(Qt.resolvedUrl("ThisWeekPage.qml"))
        }
        else if (status === PageStatus.Inactive) { view.scrollToTop() }
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
                pulley.busy = serviceStatusData.isDownloading()
            }
        }
    }

    SilicaListView {
        id: view
        anchors.fill: parent
        spacing: 10
        model: serviceStatusData.getModel()
        delegate: LineInfoWidget {
            name: nameData
            statusText: statusData
            details: messageData
            color: backgroundData
            textColor: colorData
            state: "visible"
            onClicked: { view.positionViewAtIndex(index, ListView.Contain) }
        }
        Component.onCompleted: serviceStatusData.refresh()
        onCountChanged: {
            if (footerItem) { footerItem.state = count ? "visible" : "invisible" }
        }

        header: PageHeader {
            title: "Service Status"
        }
        footer: TflNotice {}

        PullDownMenu {
            id: pulley
            MenuItem {
                text: "Refresh"
                onClicked: {
                    serviceStatusData.refresh()
                }
            }
        }
        VerticalScrollDecorator { flickable: view }
    }
}
