#include "PlotProCreator.h"

#include <QVariant>
void PlotProCreator::setXTitle(const QString& title)
{
    insertProperty("titleX", title);
}

void PlotProCreator::setYTitle(const QString& title)
{
    insertProperty("titileY", title);
}

void PlotProCreator::setTitle(const QString& title)
{
    insertProperty("title", title);
}

#include <QRectF>
void PlotProCreator::setRect(const QRectF& rect)
{
    insertProperty("scale", rect);
}

#include <QPointF>
void PlotProCreator::setSteps(const QPointF& steps)
{
    insertProperty("steps", steps);
}

#include <QSizeF>
void PlotProCreator::setExportSize(const QSizeF& exportSize)
{
    insertProperty("exportSize", exportSize);
}

void PlotProCreator::setLegendOpacity(int opacity)
{
    insertProperty("legendOpacity", opacity);
}

void PlotProCreator::setLegendPosition(int horPos, int verPos)
{
    insertProperty("legendPosHor", horPos);
    insertProperty("legendPosVer", verPos);
}
