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

Item {
    id: self
    property int type : Stop.None
    property string stopPointIndicator: ""

    height: 64
    width: 64
    Image  {
        id: icon
        source: "qrc:///waves.png"
        visible: (type === Stop.River) ? true : false
        anchors.centerIn: parent
    }
    Rectangle {
        id: busStopIcon
        height: 60
        width: height
        radius: height/2
        color: "red"
        visible: (type === Stop.Bus) ? true : false
        enabled: (type === Stop.Bus) ? true : false
        anchors.centerIn: parent
        Label {
            id: busStopIndicatorLabel
            text: stopPointIndicator
            anchors.centerIn: parent
            font.bold: true
        }
    }
}
