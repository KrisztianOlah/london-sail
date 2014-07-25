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

#include "arrivalscontainer.h"
#include <QString>
#include "arrivalsmodel.h"

ArrivalsContainer::ArrivalsContainer(ArrivalsModel* m) : model(m)
{
}


void ArrivalsContainer::add(const Vehicle& vehicle) {
    append(vehicle);
}

void ArrivalsContainer::clearData() {
    if (model) {
        model->beginReset();
    }
    clear();
    if (model) {
        model->endReset();
    }
}

void ArrivalsContainer::registerModel(ArrivalsModel* m) {
    model = m;
}

void ArrivalsContainer::replace(const ArrivalsContainer& rhs) {
    if (model) {
        model->beginReset();
        model->beginInsert(size());
    }

    if (this != &rhs) { *this = rhs; }

    if (model) {
        model->endInsert();
        model->endReset();
    }
}
