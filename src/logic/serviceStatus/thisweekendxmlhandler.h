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

#ifndef THISWEEKENDXMLHANDLER_H
#define THISWEEKENDXMLHANDLER_H

#include <QXmlDefaultHandler>
#include "linewrapper.h"

class ThisWeekendLineModel;

//This class is to parse "Weekend disruption" XML data recieved from TFL and add to its model
class ThisWeekendXmlHandler : public QXmlDefaultHandler
{
public:
    typedef LineWrapper Line;
    ThisWeekendXmlHandler(ThisWeekendLineModel* = 0);
private:
    Line aLine;
    QString currentText;
    bool inLine;
    bool inMessage;
    bool inStatus;
    ThisWeekendLineModel* model;
public:
    virtual bool characters(const QString& str);
    virtual bool endElement(const QString& namespaceURI,const QString& localName,const QString& qName);
    virtual bool startElement(const QString& namespaceURI,const QString& localName,
                              const QString& qName,const QXmlAttributes& atts);
};

#endif // THISWEEKENDXMLHANDLER_H
