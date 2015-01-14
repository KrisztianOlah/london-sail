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

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>

//This class is responsible to saving/retrieving all data that is required to/from an sqlite database on the device
class Database
{
public:
    Database();
public:
    ~Database();
private:
    QSqlDatabase db;
private:
    void close();
    int countRanked() const;
    bool createStopsTable();
    int getRank(const QString& code) const;
    bool isOpen() const;
    bool isStopsTable() const;
    bool open();
public:
    bool addStop(const QString& name,const QString& code,int type, QString& towards,double latitude, double longitude,
                 const QString& stopPointIndicator = QString(), bool favorite = false);
    bool clearStopsTable();
    bool isFavorite(const QString& code) const;
    QSqlError lastError() const; 
    bool makeFavorite(const QString& code);
    bool swapRanks(const QString& code1, const QString& code2);
    bool unFavorite(const QString& code);
};

#endif // DATABASE_H
