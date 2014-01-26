#include "SamplesManagerModel.h"

SamplesManagerModel::SamplesManagerModel(QObject *parent) :
    ListModel(parent),
    samplesManager(nullptr)
{
}

#include "SamplesManager.h"
void SamplesManagerModel::setSamplesManager(SamplesManager* samplesManager)
{
    beginResetModel();
        activeRow = -1;
        this->samplesManager = samplesManager;
    endResetModel();
}

int SamplesManagerModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return samplesManager ? samplesManager->count() : 0;
}

void SamplesManagerModel::append(const QString& pathToSrc)
{
    if(samplesManager){
        beginResetModel();
            samplesManager->append(pathToSrc);
        endResetModel();
    }
}

void SamplesManagerModel::remove()
{
    if(samplesManager){
        if(samplesManager->samplesExist(activeRow)){
            beginResetModel();
                samplesManager->remove(activeRow);
                if(activeRow > 0){
                    --activeRow;
                }
            endResetModel();
        }
    }
}

void SamplesManagerModel::replace(const QString& pathToSrc)
{
    if(samplesManager){
        if(samplesManager->samplesExist(activeRow)){
            beginResetModel();
                samplesManager->replace(activeRow, pathToSrc);
            endResetModel();
        }
    }
}

#include "Samples.h"
QString SamplesManagerModel::displayRole(const QModelIndex &index) const
{
    const Samples* samples = samplesManager->getSamples(index.row());
    return samples->getPathSrcFileInfo().fileName();
}
