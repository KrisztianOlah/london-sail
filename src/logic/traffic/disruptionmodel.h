#ifndef DISRUPTIONMODEL_H
#define DISRUPTIONMODEL_H

#include <QAbstractListModel>

class TrafficContainer;

class DisruptionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // !!! Parent MUST be a pointer to a TrafficContainer object  !!!
    explicit DisruptionModel(QObject* parent = 0);
    //TODO coordinatesRole possibly by separate long- and latiRole
    enum DisruptionRole { IDRole = Qt::UserRole + 1, LocationRole, StatusRole, SeverityRole, LevelOfInterestRole,
           CategoryRole, SubCategoryRole, StartTimeRole, CommentsRole, CurrentUpdateRole};
private:
    TrafficContainer* container;
public:
    void beginInsert(int rows);
    void beginReset();
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void endInsert();
    void endReset();
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex() ) const;
};

#endif // DISRUPTIONMODEL_H
