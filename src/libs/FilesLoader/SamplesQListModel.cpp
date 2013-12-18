#include "SamplesQListModel.h"

SamplesQListModel::SamplesQListModel(QObject *parent) :
    QAbstractListModel(parent),
    samplesManager(nullptr)
{
}

#include "SamplesManager.h"
void SamplesQListModel::setSamplesManager(SamplesManager* samplesManager)
{
    if(this->samplesManager){
        disconnect(this->samplesManager, 0, this, 0);
    }
    this->samplesManager = samplesManager;
    connect(samplesManager, SIGNAL(haveBeenAppend(int)), SLOT(resetModel()));
    connect(samplesManager, SIGNAL(haveBeenRemoved(int)), SLOT(resetModel()));
    connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(resetModel()));
}

int SamplesQListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return samplesManager ? samplesManager->count() : 0;
}

QVariant SamplesQListModel::data(const QModelIndex& index, int role) const
{
    if(role != Qt::DisplayRole || !index.isValid()){
        return QVariant();
    }
    return samplesManager->getPathToSamples(index.row());
}

bool SamplesQListModel::removeRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent)
    while(count--){
        samplesManager->remove(row);
    }
    return true;
}

void SamplesQListModel::resetModel()
{
    beginResetModel();
    endResetModel();
}
