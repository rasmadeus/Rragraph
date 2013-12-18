#ifndef ZOOMER_H
#define ZOOMER_H

#include <qwt_plot_zoomer.h>

class Zoomer : public QwtPlotZoomer
{
public:
    Zoomer(int xAxis, int yAxis, QWidget* canvas);
};

#endif // ZOOMER_H
