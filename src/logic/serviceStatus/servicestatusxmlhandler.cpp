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

#include "servicestatusxmlhandler.h"
#include <QMap>
#include <QPair>
#include <QString>
#include <QXmlAttributes>
#include "thisweekendlinemodel.h"

ServiceStatusXmlHandler::ServiceStatusXmlHandler(ThisWeekendLineModel* m) : model(m)
{
}

bool ServiceStatusXmlHandler::startElement(const QString& /*namespaceURI*/,const QString& /*localName*/,
                                           const QString& qName,const QXmlAttributes &atts) {
    if (qName == "LineStatus") {
        aLine[Line::Message] = atts.value("StatusDetails");
        return true;
    }
    if (qName == "Line") {
        aLine[Line::Name] = atts.value("Name");//it will always give the correct the name for each line
        return true;
    }
    if (qName == "Status") {
       aLine[Line::Status] = atts.value("Description");
       aLine.setColors();
       //sometimes there are more then one Status tags with attribute Description associated with the same Line (Line::Name)
       //we only save the last one which is the only one that follows the Line tag
       if (model && !aLine[Line::Name].isEmpty() ) {
           model->addLine(aLine);
           aLine = Line();
       }

       return true;
    }
    return true;
}
