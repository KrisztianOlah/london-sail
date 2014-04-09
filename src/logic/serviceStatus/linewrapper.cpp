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
