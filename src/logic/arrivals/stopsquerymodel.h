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

#ifndef STOPSQUERYMODEL_H
#define STOPSQUERYMODEL_H

#include <QSqlQueryModel>

class DatabaseManager;

//model to interact with sqlite database holding different stops
// !!! Parent MUST be a pointer to DatabaseManager object !!!
class StopsQueryModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_ENUMS(QueryTypes)
public:
    enum QueryRoles { NameRole = Qt::UserRole + 1,CodeRole,TypeRole,TowardsRole,
                      LatitudeRole,LongitudeRole, StopPointIndicatorRole };
    enum QueryTypes { Bus, Underground };
    explicit StopsQueryModel(QObject* parent = 0);
private:
    DatabaseManager* databaseManager;
public:
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;
    void showStops();
public slots:
    void clearStops();
};


#endif // STOPSQUERYMODEL_H
