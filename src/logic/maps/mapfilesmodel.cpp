#include "mapfilesmodel.h"

#include <QDebug>
#include <QStringList>

MapFilesModel::MapFilesModel(QObject *parent) : QAbstractListModel(parent)
{
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
}

QVariant MapFilesModel::data(const QModelIndex& index, int role) const {
    QFileInfoList fileList = dir.entryInfoList();
    switch (role) {
    case NameRole:
        return fileList.at(index.row()).baseName();
    case PathRole:
        return fileList.at(index.row()).absoluteFilePath();
    default:
        return QVariant();
    }
}

//To delete map file according to its index in the model
bool MapFilesModel::remove(int qmlIndex) {
    QModelIndex mi = index(qmlIndex);
    QString filePath = mi.data(PathRole).toString();

    beginRemoveRows(QModelIndex(),qmlIndex,qmlIndex);
    bool ok = dir.remove(filePath);
    endRemoveRows();
    return ok;
}

//To delete all map files that user previously downloaded
bool MapFilesModel::removeAll() {
    beginRemoveRows(QModelIndex(),0,rowCount());

    bool ok = true;
    foreach (QFileInfo info, dir.entryInfoList()) {
        //only want to know if there was a problem
        if (ok) ok  = dir.remove(info.absoluteFilePath());
        else dir.remove(info.absoluteFilePath());
    }
    dir.setPath(_rootPath);
    endRemoveRows();
    return ok;
}

//resets model
void MapFilesModel::reset() {
    setRootPath(_rootPath);
}

QHash<int,QByteArray> MapFilesModel::roleNames() const {
    QHash<int,QByteArray> hash;
    hash[NameRole] = "nameData";
    hash[PathRole] = "pathData";
    return hash;
}

int MapFilesModel::rowCount(const QModelIndex& /*parent*/) const {
    QFileInfoList fileList = dir.entryInfoList();
    return fileList.size();
}

//sets a different path to display
void MapFilesModel::setRootPath(const QString& path) {
    beginResetModel();
    _rootPath = path;
    dir.setPath(path);
    endResetModel();
}
