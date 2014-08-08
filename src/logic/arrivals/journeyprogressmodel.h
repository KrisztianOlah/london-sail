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

#ifndef JOURNEYPROGRESSMODEL_H
#define JOURNEYPROGRESSMODEL_H

#include <QAbstractListModel>

class JourneyProgressContainer;

//This is a model for Journey Progress
// !!! Parent MUST be a JourneyProgressContainer* or a nullptr !!!
class JourneyProgressModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // magic number(4) is so that JourneyProgressModel::SortRole and ArrivalsModel::EtaRole are equal
    //thus can use the same proxy model without modification
    enum JourneyProgressRole {SortRole = Qt::UserRole + 4, EtaRole, StopNameRole };
    explicit JourneyProgressModel(QObject *parent = 0);
private:
    JourneyProgressContainer* container;
public:
    void beginInsert(int first, int last);
    void beginReset();
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void endInsert();
    void endReset();
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex() ) const;
};

#endif // JOURNEYPROGRESSMODEL_H
