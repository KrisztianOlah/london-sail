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
                text: "<b>0.4.4 - New Tube Map.</b><br>
*Added new Tube Map: latest tube map as of May 2014. It takes up considerably more space due to higher resolution and better colours.<br>
*Added Pulley menu to Bus Stop Page: it is now possible to manually refresh the data,
 added a widget to indicate when the timer would refresh automatically.<br>
*Fixed bug: cover no longer shows TERMINATED while bus is still on route."
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
                text: "<b>0.4.3 - Bus Maps.</b><br>
*Added Bus Maps: it is now possible to download, delete and to open(with default pdf reader) bus maps.<br>
*Fixed bug: on Bus Departures Page text can no longer be outside of its widget."
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
                text: "<b>0.4.2 - Bus Stop Messages.</b><br>
*Added Bus stop messages: relevant messages now appear in the header.<br>
*Fixed bug: Widgets in This Weekend and Service Status pages' expand and contract consistently and text is displayed only inside widget.<br>
*Pulley menu is now disabled on This Weekend and Service Status pages when busy to avoid possible segfault.
*Fixed bug: on Bus Stop page BusyIndicator is now correctly shown whilst dowloading.<br>
*Fixed bug: on Journey Progress page placeholder is now not visible during downloading.<br>
*Other minor GUI improvements."
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
                text: "<b>0.4.1 - Bug fixes.</b><br>
*Fixed bug: that was causing client to terminate unexpectedly.<br>
*Fixed bug: Cover now displays TERMINATED after last stop has been reached.<br>
*Piers have received a new icon.<br>
*Other minor GUI improvements."
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
*Changed cover picture to accomodate the new cover information."
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
*Fixed bug: Service Status and This Weekend colours match as intended."
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
