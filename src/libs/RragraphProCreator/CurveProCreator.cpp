#include "CurveProCreator.h"

#include <QString>
#include <QVariant>
void CurveProCreator::setAddendX(double addend)
{
    insertProperty("addendX", addend);
}

void CurveProCreator::setAddendY(double addend)
{
    insertProperty("addendY", addend);
}

void CurveProCreator::setColor(const QString& color)
{
    insertProperty("color", color);
}

void CurveProCreator::setDashPattern(const QString& dashPattern)
{
    insertProperty("dashPattern", dashPattern);
}

void CurveProCreator::setMultY(double addend)
{
    insertProperty("multY", addend);
}

void CurveProCreator::setSymbolStyle(int style)
{
    insertProperty("symbolStyle", style);
}

void CurveProCreator::setWidth(int width)
{
    insertProperty("width", width);
}

void CurveProCreator::setStep(int step)
{
    insertProperty("step", step);
}

void CurveProCreator::setY(int iY)
{
    insertProperty("indexY", iY);
}
