#include "LegendItem.h"

#include <qwt_plot.h>
LegendItem::LegendItem(QwtPlot* owner)
{
    setRenderHint(QwtPlotItem::RenderAntialiased);
    setTextPen(QPen(Qt::black));
    setBackgroundOpacity(200);
    setBackgroundMode(ItemBackground);
    setBorderRadius(4);
    setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    setMargin(0);
    setSpacing(4);
    setItemMargin(2);    
    attach(owner);
}

void LegendItem::setBackgroundOpacity(int alpha)
{
    setBorderPen(QPen(QColor(0, 0, 0, alpha)));
    setBackgroundBrush(QColor(255, 255, 255, alpha));
}

Qt::AlignmentFlag LegendItem::getHorPos() const
{
    if(alignment().testFlag(Qt::AlignHCenter)){
        return Qt::AlignHCenter;
    }
    if(alignment().testFlag(Qt::AlignLeft)){
        return Qt::AlignLeft;
    }
    return Qt::AlignRight;
}

Qt::AlignmentFlag LegendItem::getVerPos() const
{
    if(alignment().testFlag(Qt::AlignVCenter)){
        return Qt::AlignVCenter;
    }
    if(alignment().testFlag(Qt::AlignTop)){
        return Qt::AlignTop;
    }
    return Qt::AlignBottom;
}
