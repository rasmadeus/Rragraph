#ifndef CANVAS_H
#define CANVAS_H

class Zoomer;
#include <qwt_plot_canvas.h>
#include "global.h"

class Canvas : public QwtPlotCanvas
{
    Q_OBJECT
    Zoomer* zoomer;
public:
    explicit Canvas(QwtPlot* parent);
signals:
    void zoomed();
};

#endif // CANVAS_H
