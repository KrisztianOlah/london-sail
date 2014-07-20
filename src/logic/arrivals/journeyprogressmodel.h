#ifndef JOURNEYPROGRESSMODEL_H
#define JOURNEYPROGRESSMODEL_H

#include <QAbstractListModel>

class JourneyProgressContainer;

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
