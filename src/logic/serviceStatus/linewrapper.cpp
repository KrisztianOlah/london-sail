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


#include "linewrapper.h"
#include <QDebug>
#include <QString>

namespace {
QHash<QString,QString> makeBgColorHash() {
    QHash<QString,QString> hash;
    hash["Bakerloo"] = "#AE6118";
    hash["Central"] = "#E41F1F";
    hash["Circle"] = "#F8D42D";
    hash["District"] = "#007229";
    hash["DLR"] = "#00BBB4";
    hash["Hammersmith and City"] = "#E899A8";
    hash["Jubilee"] = "#686E72";
    hash["Metropolitan"] = "#893267";
    hash["Northern"] = "#000000";
    hash["Overground"] = "#F86C00";
    hash["Piccadilly"] = "#0450A1";
    hash["Victoria"] = "#009FE0";
    hash["Waterloo and City"] = "#70C3CE";
    return hash;
}

QHash<QString,QString> makeTxtColorHash() {
    QHash<QString,QString> hash;
    hash["Circle"] = "#113B92";
    hash["Hammersmith and City"] = "#113B92";
    hash["Waterloo and City"] = "#113B92";
    return hash;
}
}//end unamed namespace

QHash<QString,QString> LineWrapper::bgColorHash = makeBgColorHash();

QHash<QString,QString> LineWrapper::txtColorHash = makeTxtColorHash();


//FIX function try block
LineWrapper::LineWrapper() : data(new QString[size]),
                             pRefCount(new int(1))
{
}

LineWrapper::LineWrapper(const LineWrapper& other) : pRefCount(other.pRefCount) {
    data = other.data;
    pRefCount = other.pRefCount;
    ++(*pRefCount);
}
//only delete data and refcount pointer when it's the last object pointing there
LineWrapper::~LineWrapper() {
    if (!--(*pRefCount)) {
        delete pRefCount;
        delete [] data;
    }
}

//public:
QString LineWrapper::getBgColor(const QString& line) { return bgColorHash.value(line); }

QString LineWrapper::getTxtColor(const QString& line) {
    QString retVal = txtColorHash.value(line);
    return (retVal == "") ? "#FFFFFF" : retVal;
}

void LineWrapper::setColors() {
    data[Background] = getBgColor(data[Name]);
    data[Colour] = getTxtColor(data[Name]);
}


LineWrapper& LineWrapper::operator=(const LineWrapper& rhs) {
    if (&rhs != this) {
        //decrement OLD refcount, if last obj delete its data
        if (!--(*pRefCount)) {
            delete pRefCount;
            delete [] data;
        }
        data = rhs.data;
        pRefCount = rhs.pRefCount;
        ++(*pRefCount);//increment NEW refCount
    }
    return *this;
}


QString& LineWrapper::operator[](int index) { return data[index]; }

const QString& LineWrapper::operator[](int index) const { return const_cast<QString&>(this->operator[](index)); }
