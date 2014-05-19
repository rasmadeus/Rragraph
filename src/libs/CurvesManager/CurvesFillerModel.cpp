#include "CurvesFillerModel.h"

CurvesFillerModel::CurvesFillerModel(QObject *parent) :
    QAbstractTableModel(parent),
    curves(nullptr)
{
}

void CurvesFillerModel::setCurves(Curves* curves)
{
    beginResetModel();
        this->curves = curves;
    endResetModel();
}

#include "Curves.h"
#include <Samples.h>
bool CurvesFillerModel::samplesAvailaible() const
{
    return curves && !curves->getSamples()->isLoading();
}

int CurvesFillerModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return samplesAvailaible() ? curves->getSamples()->count() : 0;
}

int CurvesFillerModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return samplesAvailaible() ? 2 : 0;
}

QVariant CurvesFillerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(section){
            case 0: return tr("X");
            case 1: return tr("Y");
        }
    }
    return QVariant();
}

bool CurvesFillerModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    Q_UNUSED(value)
    if(role != Qt::EditRole){
        return false;
    }
    beginResetModel();
        switch (index.column()){
            case 0: curves->setX(index.row()); break;
            case 1: curves->setY(index.row()); break;
        }
    endResetModel();
    emit dataWasSetted();
    return true;
}

bool CurvesFillerModel::isActiveX(const QModelIndex& index) const
{
    return index.column() == 0 && curves->isX(index.row());
}

bool CurvesFillerModel::isActiveY(const QModelIndex& index) const
{
    return index.column() == 1 && curves->isY(index.row());
}

QString CurvesFillerModel::getDisplayRole(const QModelIndex& index) const
{
    switch(index.column()){
        case 0: return curves->getSamples()->getProxyHeader(index.row());
        case 1: return isActiveY(index) ? tr("Yes") : tr("No");
    }
    return QString();
}

#include <QColor>
QColor CurvesFillerModel::getTextColorRole(const QModelIndex& index) const
{
    return QColor(isActiveXorY(index) ? "red" : "black");
}

#include <QFont>
QFont CurvesFillerModel::getFontRole(const QModelIndex& index) const
{
    QFont res;
    if(isActiveXorY(index)){
        res.setBold(true);
    }
    return res;
}

QVariant CurvesFillerModel::data(const QModelIndex& index, int role) const
{
    switch(role){
        case Qt::DisplayRole: return getDisplayRole(index);
        case Qt::TextColorRole: return getTextColorRole(index);
        case Qt::FontRole: return getFontRole(index);
    }
    return QVariant();
}

Qt::ItemFlags CurvesFillerModel::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool CurvesFillerModel::isActiveXorY(const QModelIndex& index) const
{
    return isActiveX(index) || isActiveY(index);
}

void CurvesFillerModel::resetModel()
{
    beginResetModel();
    endResetModel();
}
