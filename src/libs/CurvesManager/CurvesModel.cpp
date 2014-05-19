#include "CurvesModel.h"

CurvesModel::CurvesModel(QObject *parent) :
    ListModel(parent),
    curves(nullptr)
{
}

#include "Curves.h"
void CurvesModel::setCurves(Curves* curves)
{
    beginResetModel();
        this->curves = curves;
        activeRow = -1;  
    endResetModel();
}

int CurvesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return curves ? curves->count() : 0;
}

#include "Curve.h"
QString CurvesModel::displayRole(const QModelIndex& index) const
{ 
    return getCurve(index)->title().text();
}

QColor CurvesModel::textColorRole(const QModelIndex& index) const
{
    return getCurve(index)->isVisible() ? QColor(0, 0, 0) : QColor(200, 200, 200);
}

Curve* CurvesModel::getCurve(const QModelIndex& index) const
{
    return curves->getCurve(index);
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
