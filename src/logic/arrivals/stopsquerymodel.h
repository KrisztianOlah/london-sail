#ifndef STOPSQUERYMODEL_H
#define STOPSQUERYMODEL_H

#include <QSqlQueryModel>

class DatabaseManager;

class StopsQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum QueryRoles { NameRole = Qt::UserRole + 1,CodeRole,TypeRole,TowardsRole,
                      LatitudeRole,LongitudeRole, StopPointIndicatorRole };
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
