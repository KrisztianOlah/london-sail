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

//This page will show all the changes that have occured since first release
Page {
    id: page
    allowedOrientations: Orientation.All

    onStatusChanged: {
                if (status === PageStatus.Active) { coverData.reportPage(PageCodes.None) }
    }

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge
        VerticalScrollDecorator { flickable: flick }
        Column {
            id: column
            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: "Changelog"
            }
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                textFormat: Text.RichText
                text: "<b>0.4.0 - Bus and River Bus Departures Feature.</b><br>
*Changed cover picture to accomodate the new cover information"
            }
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                textFormat: Text.RichText
                text: "<b>0.3.2 - Hotfix.</b><br>
*Fixed bug: Service Status now works as intended."
            }
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                textFormat: Text.RichText
                text: "<b>0.3.1 - Road Disruptions filters.</b><br>
*Added filters to Road Disruption page.<br>
*Fixed bug: Road Disruptions page now correctly displays all labels. No more empty labels.<br>
*Minor GUI improvements."
            }
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                textFormat: Text.RichText
                text: "<b>0.3.0 - Road Disruptions Feature.</b><br>
*Fixed bug: Service Status/This Weekend now correctly displays special characters(&, ', etc)<br>
*Fixed bug: Service Status and This Weekend colours match as intended"
            }

            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                text: "0.2.0 - This Weekend feature."
                font.bold: true
            }

            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                text: "0.1.0 - Initial release."
                font.bold: true
            }
        }
    }
}
