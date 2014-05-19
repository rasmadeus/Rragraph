#ifndef CANVAS_H
#define CANVAS_H

class Zoomer;
#include <qwt_plot_canvas.h>
#include <qwt_point_3d.h>

class Canvas : public QwtPlotCanvas
{
    Q_OBJECT
public:
    explicit Canvas(QwtPlot* parent);
    void setZoomBase();
    void setZoomStack(const QRectF& rect);
Q_SIGNALS:
    void zoomed();
private:
    Zoomer* zoomer;
};

#endif // CANVAS_H
