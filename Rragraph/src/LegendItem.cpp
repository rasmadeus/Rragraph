#include "LegendItem.h"

#include <qwt_plot.h>
LegendItem::LegendItem(QwtPlot* owner)
{
    setRenderHint(QwtPlotItem::RenderAntialiased);
    setTextPen(QPen(Qt::black));
    setBorderPen(QPen(QColor(0, 0, 0, 200)));
    setBackgroundBrush(QColor(255, 255, 255, 200));
    setBackgroundMode(ItemBackground);
    setBorderRadius(4);
    setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    setMargin(0);
    setSpacing(4);
    setItemMargin(2);    
    attach(owner);
}
