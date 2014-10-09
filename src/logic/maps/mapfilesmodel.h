#ifndef MAPFILESMODEL_H
#define MAPFILESMODEL_H

#include <QAbstractListModel>
#include <QDir>


class MapFilesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum FileRoles { NameRole = Qt::UserRole, PathRole };
    explicit MapFilesModel(QObject *parent = 0);
private:
    QDir dir;
public:
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE bool remove(int index);
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    void setRootPath(const QString& path);
};

#endif // MAPFILESMODEL_H
