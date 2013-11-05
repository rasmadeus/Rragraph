#ifndef LEGENDITEM_H
#define LEGENDITEM_H

#include <qwt_plot_legenditem.h>
#include <QJsonObject>

class LegendItem : public QwtPlotLegendItem
{
public:
    explicit LegendItem(QwtPlot* owner);
    void serialize(QJsonObject& plot);
    void restore(const QJsonObject& plot);
    void setBackgroundOpacity(int alpha);
    Qt::AlignmentFlag getHorPos() const;
    Qt::AlignmentFlag getVerPos() const;
};

#endif // LEGENDITEM_H
