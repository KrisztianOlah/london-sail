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

#ifndef DISRUPTION_H
#define DISRUPTION_H

#include <QString>

struct Disruption
{
    Disruption();

//    enum Status { Active, ActiveLT, Scheduled, Recurring,  Cleared };
//    enum Interest { Low, Medium, High };

    int id;
    QString category;
    QString coordinates;
    QString comments;
    QString currentUpdate;
    QString endTime;//QDateTime
    QString lastModTime;//QDateTime
    QString levelOfInterest;//can be used later to deterine a score by which data can be displayed
    QString location;
    QString severity;
    QString remarkTime;//QDateTime //Time of currentupdate
    QString startTime;//QDateTime
    QString status;
    QString subCategory;
};

#endif // DISRUPTION_H

