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

#ifndef STOP_H
#define STOP_H

#include <QString>
#include <QObject>

class DatabaseManager;

//This class is to hold a bus/river stop or tube/overground/dlr station and its data
// !!! Parent MUST be a pointer to a DatabaseManager object !!!
class Stop : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)

public:
    explicit Stop(QObject*  parent = 0);
    enum Type { None, Bus, Underground, River, Overground, Dlr};
private:
    DatabaseManager* databaseManager;
    QString id;
    double latitude;//will be replaced with QCoordinates
    double longitude;//   -||-
    QString name;
    QString stopPointIndicator;//for bus stops
    QString towards;//might be empty string for some types such as Underground
    int type;
public:
    void addToDb();
    void setID(const QString&);
    void setLatitude(double);
    void setLongitude(double);
    void setName(const QString&);
    void setStopPointIndicator(const QString&);
    void setTowards(const QString&);
    void setType(int);
    void updated();
signals:
    void dataChanged();
public slots:
    void clear();
    QString getID() const;
    double getLatitude() const;
    double getLongitude() const;
    QString getName() const;
    QString getStopPointIndicator() const;
    QString getTowards() const;
    int getType() const;
};

#endif // STOP_H
