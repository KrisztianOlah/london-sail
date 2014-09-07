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


//adds a new vehicle, it shouldn't be called on containers whose models are connected to views
void ArrivalsContainer::add(const Vehicle& vehicle) {
    append(vehicle);
}

//clears data and notifies model about it
void ArrivalsContainer::clearData() {
    if (model) {
        model->beginRemove();
    }
    clear();
    if (model) {
        model->endRemove();
    }
}

//when a model is created a model can register itself with a container
//so that they both have a pointer of each other and can call each other's methods
void ArrivalsContainer::registerModel(ArrivalsModel* m) {
    model = m;
}

//swaps another contaier for this and notifies model that a drastic change happened
//swap so that even when a download goes awry there is data to display to user
void ArrivalsContainer::replace(const ArrivalsContainer& rhs) {
    if (model) {
        clearData();
        model->beginInsert(rhs.size() - 1);
    }

    if (this != &rhs) { *this = rhs; }

    if (model) {
        model->endInsert();
    }
}
