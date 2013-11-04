#ifndef LEGENDITEM_H
#define LEGENDITEM_H

#include <qwt_plot_legenditem.h>

class LegendItem : public QwtPlotLegendItem
{
public:
    explicit LegendItem(QwtPlot* owner);
};

#endif // LEGENDITEM_H
