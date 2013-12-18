#include "HeadersModel.h"

#include "HeaderSamples.h"
#include "Files.h"
HeadersModel::HeadersModel(QObject *parent) :
    QAbstractListModel(parent),
    iFile(-1)
{   
    samples = HeaderSamples::getInstance();
    connect(Files::getInstance(), SIGNAL(headersWasParsed(int)), SLOT(reset(int)));
}

int HeadersModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return samples->size(iFile);
}

QVariant HeadersModel::data(const QModelIndex& index, int role) const
{
    if(!(index.isValid() && role == Qt::DisplayRole)){
        return QVariant();
    }
    return samples->getHeader(iFile, index.row());
}

bool HeadersModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(role != Qt::EditRole || !index.isValid()){
        return false;
    }
    samples->setHeader(iFile, index.row(), value.toString());
    return true;
}

#include "Samples.h"
void HeadersModel::wasChoosen(int iFile)
{
    beginResetModel();
        this->iFile = iFile;
    endResetModel();
}

#include <stdexcept>
void HeadersModel::reset(int iFile)
{
    //It need in try catch because of Files' signal wasRemoved(iFile) and
    //this invoke(iFile) reset may be in the same time.
    try{
        samples->reset(iFile);
    }
    catch(const std::out_of_range& err){
        Q_UNUSED(err)
        return;
    }

    if(this->iFile == iFile){
        wasChoosen(iFile);
    }
}

Qt::ItemFlags HeadersModel::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
