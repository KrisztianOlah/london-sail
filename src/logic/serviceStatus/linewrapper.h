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

#ifndef LINEWRAPPER_H
#define LINEWRAPPER_H

#include <QString>
#include <QHash>

//This class is to store a Line object conviniently where Line's properties are accessed with linewrapper[enum]
//LineWrapper is a RAII class that is responsible take care of deleting its data when reference count goes down to 0
class LineWrapper
{
public:
    LineWrapper();
    LineWrapper(const LineWrapper&);
    ~LineWrapper();
    enum { Name, Status, Message, Colour, Background };
private:
    static QHash<QString,QString> bgColorHash;
    static QHash<QString,QString> txtColorHash;
    QString* data;
    int* pRefCount;
    static const int size = 5;
public:
    QString getBgColor(const QString& line);
    QString getTxtColor(const QString& line);
    void setColors();
public:
    LineWrapper& operator=(const LineWrapper&);
    QString& operator[](int index);
    const QString& operator[](int index) const;
};

#endif // LINEWRAPPER_H
