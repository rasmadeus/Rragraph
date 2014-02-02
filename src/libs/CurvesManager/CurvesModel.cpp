#include "CurvesModel.h"

CurvesModel::CurvesModel(QObject *parent) :
    ListModel(parent),
    curves(nullptr)
{
}

void CurvesModel::setCurves(Curves* curves)
{
    beginResetModel();
        this->curves = curves;
        activeRow = -1;
    endResetModel();
}

#include "Curves.h"
int CurvesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return curves ? curves->count() : 0;
}

#include "Curve.h"
QString CurvesModel::displayRole(const QModelIndex& index) const
{
    Curve* curve = curves->getCurve(index);    
    return curve->title().text();
}

Curve* CurvesModel::getCurve() const
{
    return curves->getCurveFrom(activeRow);
}

Plot* CurvesModel::getOwner() const
{
    return curves->getOwner();
}

Curves* CurvesModel::getCurves() const
{
    return curves;
}
