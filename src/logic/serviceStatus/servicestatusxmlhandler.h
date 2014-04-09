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

#ifndef SERVICESTATUSXMLHANDLER_H
#define SERVICESTATUSXMLHANDLER_H


#include <QMap>
#include <QPair>
#include <QString>
#include <QXmlDefaultHandler>

//ServiceStatusXmlHandler is responsible of parsing the the fetched Service Status data and putting
//them in a container provided by the caller.

class ServiceStatusXmlHandler : public QXmlDefaultHandler
{
public:
    ServiceStatusXmlHandler(QMap<QString,QPair<QString,QString> >* c);
public:
    bool startElement(const QString& namespaceURI,const QString& localName,const QString& qName,const QXmlAttributes& atts);
private:
    QMap<QString,QPair<QString,QString> >* container;
    QString details;
    QString lineName;

};

#endif // SERVICESTATUSXMLHANDLER_H
