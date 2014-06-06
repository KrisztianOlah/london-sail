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
    allowedOrientations: Orientation.All

    property string location: ""
    property string comment: ""
    property string currentUpdate: ""
    property string severity: ""
    property int disruptionID: 0
    property StreetModel streetModel: trafficData.getStreetModel(disruptionID)
    SilicaFlickable {
        id: flick
        anchors.fill: parent

        contentHeight: column.height

        state: (streetModel.count() ) ? "visibleStreets" : "invisibleStreets"

        VerticalScrollDecorator { flickable: flick }

        Column {
            id: column
            width: page.width
            spacing: 10

            PageHeader {
                title: "Disruption Details"
            }

            RoadDetailsWidget {
                id: detailsWidget
                location: page.location
                comment: page.comment
                currentUpdate: page.currentUpdate
                state: page.severity
            }
            Item {
                id: topExtraSpace
                height: 30
                width: 1
            }

            Label {
                id: secondaryHeader
                text: "Affected Roads/Streets"
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor
                anchors {
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
            }
            Item {
                id: middleExtraSpace
                height: 30
                width: 1
            }

            Repeater {
                model: streetModel
                StreetWidget {
                    name: nameData
                    closure: closureData
                    direction: directionsData
                }
            }
            TflNotice {
                state: "visible"
            }
        }
        states: [
            State {
            name: "visibleStreets"
            PropertyChanges {
                target: secondaryHeader
                opacity: 100
            }
            PropertyChanges {
                target: topExtraSpace
                width: 1
            }
            PropertyChanges {
                target: middleExtraSpace
                width: 1
            }
        },
        State {
                name: "invisibleStreets"
                PropertyChanges {
                    target: secondaryHeader
                    opacity: 0
                    height: Theme.paddingLarge
                }
                PropertyChanges {
                    target: topExtraSpace
                    width: 0
                }
                PropertyChanges {
                    target: middleExtraSpace
                    width: 0
                }
            }
        ]
    }
}
