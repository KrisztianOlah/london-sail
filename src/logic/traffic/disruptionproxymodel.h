#ifndef DISRUPTIONPROXYMODEL_H
#define DISRUPTIONPROXYMODEL_H

#include <QSortFilterProxyModel>

class DisruptionProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit DisruptionProxyModel(QObject *parent = 0);
protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
public slots:
    void filter(const QString& str);

};

#endif // DISRUPTIONPROXYMODEL_H
