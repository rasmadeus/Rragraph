#include "SamplesProxyModel.h"

SamplesProxyModel::SamplesProxyModel(QObject *parent) :
    QAbstractTableModel(parent),
    samples(nullptr)
{
}

#include "Samples.h"
int SamplesProxyModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return samples && !samples->isLoading() ? samples->count() : 0;
}

int SamplesProxyModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant SamplesProxyModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole){
        const int i = index.row();
        switch(index.column()){
            case 0: return samples->getProxyHeader(i);
            case 1: return samples->getProxyColumnAddend(i);
            case 2: return samples->getProxyColumnMult(i);
        }
    }
    return QVariant();
}

bool SamplesProxyModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(role == Qt::EditRole){
            const int i = index.row();
        beginResetModel();
            switch(index.column()){
                case 0: samples->setProxyHeader(value.toString(), i); break;
                case 1: samples->setProxyColumnAddend(value.toDouble(), i); break;
                case 2: samples->setProxyColumnMult(value.toDouble(), i); break;
            }
        endResetModel();
        return true;
    }
    return false;
}

QVariant SamplesProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(section){
            case 0: return tr("Headers");
            case 1: return tr("Addend");
            case 2: return tr("Multiple");
        }
    }
    return QVariant();
}

Qt::ItemFlags SamplesProxyModel::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void SamplesProxyModel::setSamples(Samples* samples)
{
    beginResetModel();
        this->samples = samples;
    endResetModel();
}

void SamplesProxyModel::resetAddend()
{
    beginResetModel();
        samples->resetProxyAddend();
    endResetModel();
}

void SamplesProxyModel::resetHeaders()
{
    beginResetModel();
        samples->resetProxyHeaders();
    endResetModel();
}

void SamplesProxyModel::resetMult()
{
    beginResetModel();
        samples->resetProxyMult();
    endResetModel();
}
