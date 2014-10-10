#ifndef MAPFILESMODEL_H
#define MAPFILESMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QFileInfoList>


class MapFilesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum FileRoles { NameRole = Qt::UserRole, PathRole };
    explicit MapFilesModel(QObject *parent = 0);
private:
    QDir dir;
    QString _rootPath;
//    QFileInfoList fileList;
public:
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE bool remove(int index);
    Q_INVOKABLE bool removeAll();
    Q_INVOKABLE void reset();
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    void setRootPath(const QString& path);
};

#endif // MAPFILESMODEL_H
