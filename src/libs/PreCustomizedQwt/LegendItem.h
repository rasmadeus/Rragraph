#ifndef LEGENDITEM_H
#define LEGENDITEM_H

class QJsonObject;
#include <qwt_plot_legenditem.h>

class LegendItem : public QwtPlotLegendItem
{
public:
    explicit LegendItem(QwtPlot* owner);
    void setBackgroundOpacity(int alpha);
    Qt::AlignmentFlag getHorPos() const;
    Qt::AlignmentFlag getVerPos() const;
};

#endif // LEGENDITEM_H
