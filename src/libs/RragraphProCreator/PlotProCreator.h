#ifndef PLOTPROCREATOR_H
#define PLOTPROCREATOR_H

#include "ObjectProCreator.h"
class QRectF;
class QPointF;
class QSizeF;

class PlotProCreator: public ObjectProCreator
{
public:
    void setTitle(const QString& title);
    void setXTitle(const QString& title);
    void setYTitle(const QString& title);
    void setRect(const QRectF& rect);
    void setSteps(const QPointF& steps);
    void setExportSize(const QSizeF& size);
    void setLegendOpacity(int opacity);
    void setLegendPosition(int horPos, int verPos);
};

#endif // PLOTPROCREATOR_H
