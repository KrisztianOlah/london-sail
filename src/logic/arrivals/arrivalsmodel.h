#ifndef ARRIVALSMODEL_H
#define ARRIVALSMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QString>

class ArrivalsContainer;

class ArrivalsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ArrivalsRoles { IdRole = Qt::UserRole + 1, LineRole, DestinationRole, EtaRole, TowardRole, PlatformRole };
    explicit ArrivalsModel(ArrivalsContainer* = 0, QObject *parent = 0);
private:
    ArrivalsContainer* container;
public:
    void beginInsert(int rows);
    void beginReset();
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void endInsert();
    void endReset();
    void replaceContainer(const ArrivalsContainer&);
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex() ) const;
};

#endif // ARRIVALSMODEL_H

