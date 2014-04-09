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


#include "thisweekendxmlhandler.h"
#include <QDebug>
#include "linewrapper.h"
#include "thisweekendlinemodel.h"

ThisWeekendXmlHandler::ThisWeekendXmlHandler(ThisWeekendLineModel* m) : inLine(false),
                                                                        inMessage(false),
                                                                        inStatus(false),
                                                                        model(m)
{
}

//public
bool ThisWeekendXmlHandler::characters(const QString &str) {
    currentText += str;
    return true;
}

//called when closing XML element found
bool ThisWeekendXmlHandler::endElement(const QString& /*namespaceURI*/,const QString& /*localName*/,const QString &qName) {
    if (qName == "Line") {
        inLine = false;
        if (model) { model->addLine(aLine);}
    }
    else if (qName == "Message") { inMessage = false; }
    else if (qName == "Status") { inStatus = false; }


    else if (qName == "Name" && inLine) {
        aLine[Line::Name] = (currentText == "H'smith & City") ? "Hammersmith & City" : currentText;
    }
    else if (qName == "Colour" && inLine && !inStatus) {
        QString colour;
        QString number = (currentText == "FFF") ? "FFFFFF" : currentText;
        colour = QString("#") + number;
        aLine[Line::Colour] = colour;
    }
    else if (qName == "BgColour" && inLine && !inStatus) {
        QString background("#");
        background += currentText;
        aLine[Line::Background] = background;
    }
    else if (qName == "Text" && inLine) {
        if (inMessage && inStatus) {
                    aLine[Line::Message] = currentText;
                }
        else if (!inMessage && inStatus) {
            aLine[Line::Status] = currentText;
        }
    }
    return true;
}

//called when opening xml element found
bool ThisWeekendXmlHandler::startElement(const QString& /*namespaceURI*/,const QString& /*localName*/,
                                         const QString& qName,const QXmlAttributes& /*atts*/) {
    if (qName == "Line") {
        inLine = true;
        //if it's a new line use a new LineWrapper object
        aLine = Line();
    }
    else if (qName == "Status") { inStatus = true; }
    else if (qName == "Message") { inMessage = true; }

    else if (qName == "Name" || qName == "Text" || qName == "Colour" || qName == "BgColour") {
        currentText = "";
    }
    return true;
}


