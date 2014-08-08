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


#include "databasemanager.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QVariant>


DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent)
{
}

//public:
//adds a stop in DATA database, returns true on success and false otherwise
bool DatabaseManager::addStop(const QString& name,const QString& code,int type, QString& towards, double latitude, double longitude,
             const QString& stopPointIndicator, bool favorite) {
    return db.addStop(name, code, type, towards, latitude, longitude, stopPointIndicator, favorite);
}

//clears stopstable from unfavorited stops, returns true on success and false otherwise
bool DatabaseManager::clearStopsTable() { return db.clearStopsTable(); }

//checks if a stop is favorite
bool DatabaseManager::isFavorite(const QString& code) { return db.isFavorite(code); }

//makes a stop favorite, returns true on success and false otherwise
bool DatabaseManager::makeFavorite(const QString& code) { return db.makeFavorite(code); }

//makes a stop to be not favorite, returns true on success and false otherwise
bool DatabaseManager::unFavorite(const QString& code) { return db.unFavorite(code); }
