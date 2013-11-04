#include "FilesModel.h"

SINGLETON_IMPLEMENTATION(FilesModel)

#include "Files.h"
FilesModel::FilesModel(QObject *parent) :
    QAbstractListModel(parent)
{
    files = Files::getInstance();
    connect(files, SIGNAL(wasAdded(int)), SLOT(reset()));
    connect(files, SIGNAL(wasRemoved(int)), SLOT(reset()));
}

int FilesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return files->countSamples();
}

QVariant FilesModel::data(const QModelIndex& index, int role) const
{
    return role == Qt::DisplayRole ? files->getPath(index.row()).fileName() : QVariant();
}

void FilesModel::reset()
{
    beginResetModel();
    endResetModel();
}
