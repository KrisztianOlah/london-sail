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

//This page is just to show some general information to user about the application
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
            PageHeader {title: "About London Sail" }
            Image {
                source: "/usr/share/icons/hicolor/86x86/apps/harbour-london-sail.png"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label {
                id: versionLabel
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge * 2
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                text: "Version: 0.4.5"
            }
            Label {
                id: descriptionLabel
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                text: "London Sail is aimed at Londoners to help them with their daily commute.

Please note that the Bus Maps feature requires a pdf reader (such as Documents app  by Jolla) installed in order to open the maps.

More features to come..."
            }

            Label {
                id: copyrightLabel
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                text: "Copyright © 2014 Krisztian Olah"
            }
            Label {
                id: tflNotice
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                text: "Data kindly provided by <html><a href='http://www.tfl.gov.uk/'>TfL</a></html>.
                       The London Underground map is the property of Transport for London.

This software is not in any way affiliated with TfL."
                linkColor: Theme.primaryColor
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                id: licenseLabel
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }

                text: 'This software is licensed under the <html><a href="LicensePage.qml">MIT License</a></html>.'
                onLinkActivated: pageStack.push(Qt.resolvedUrl(link))
                linkColor: Theme.primaryColor
            }
            Label {
                id: hostedLabel
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                text: 'The project is hosted on <html><a href="https://github.com/KrisztianOlah/london-sail">GitHub</a></html>.'
                linkColor: Theme.primaryColor
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                id: thanksLabel
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                text: "Many thanks to my friend and mentor Anatoly Kozlov."
            }
            //Disabled until there is any change to show
            Button {
                text: "Changelog"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: pageStack.push(Qt.resolvedUrl("ChangelogPage.qml"))
            }
        }
    }
}

