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

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "database.h"

class QSqlDatabase;

//this class is to interact with different databases(data, settings, etc...`)
class DatabaseManager : public QObject
{
public:
    explicit DatabaseManager(QObject* parent = 0);
private:
    Database db;
public:
    bool addStop(const QString& name,const QString& code,int type, QString& towards,double latitude, double longitude,
                 const QString& stopPointIndicator = QString(), bool favorite = false);
    bool areTubeStationsInDB();
    bool clearStopsTable();
    bool importStations();
    bool isFavorite(const QString& code);
    bool makeFavorite(const QString& code);
    bool move(const QString& from, const QString& to);
    bool unFavorite(const QString& code);
};

#endif // DATABASEMANAGER_H
