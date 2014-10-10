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

bool MapFilesModel::remove(int qmlIndex) {
    QModelIndex mi = index(qmlIndex);
    QString filePath = mi.data(PathRole).toString();

    beginRemoveRows(QModelIndex(),qmlIndex,qmlIndex);
    bool ok = dir.remove(filePath);
    endRemoveRows();
    return ok;
}

void MapFilesModel::reset() {
    beginResetModel();
    endResetModel();
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

void MapFilesModel::setRootPath(const QString& path) {
    beginResetModel();
    dir.setPath(path);
    endResetModel();
}
