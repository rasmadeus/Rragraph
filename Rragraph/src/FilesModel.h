#ifndef FILESMODEL_H
#define FILESMODEL_H

class Files;
#include "global.h"
#include <QAbstractListModel>

class FilesModel : public QAbstractListModel
{
    Q_OBJECT
    SINGLETON_HEADER(FilesModel)
    Files* files;
public:
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
private slots:
    void reset();
};

#endif // FILESMODEL_H
