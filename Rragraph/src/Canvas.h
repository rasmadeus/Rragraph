#ifndef CANVAS_H
#define CANVAS_H

class Zoomer;
#include <qwt_plot_canvas.h>
#include "global.h"

class Canvas : public QwtPlotCanvas
{
    Q_OBJECT
public:
    explicit Canvas(QwtPlot* parent);
    void setZoomBase();
signals:
    void zoomed();
private:
    Zoomer* zoomer;
};

#endif // CANVAS_H
