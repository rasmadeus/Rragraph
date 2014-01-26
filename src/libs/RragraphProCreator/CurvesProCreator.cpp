#include "CurvesProCreator.h"

void CurvesProCreator::clear()
{
    curves = QJsonArray();
    ObjectProCreator::clear();
}

void CurvesProCreator::fill(QJsonArray& curves) const
{
    obj.insert("curves", this->curves);
    ObjectProCreator::fill(curves);
}

#include "CurveProCreator.h"
void CurvesProCreator::append(const CurveProCreator &curve)
{
    curve.fill(curves);
}

#include<QVariant>
void CurvesProCreator::setX(int iX)
{
    insertProperty("indexX", iX);
}

void CurvesProCreator::setFile(int iFile)
{
    insertProperty("indexFile", iFile);
}

void CurvesProCreator::setPlot(int iPlot)
{
    insertProperty("indexPlot", iPlot);
}
