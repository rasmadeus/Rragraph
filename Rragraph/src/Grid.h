#ifndef GRID_H
#define GRID_H

#include <qwt_plot_grid.h>

class Grid : public QwtPlotGrid
{
public:
    explicit Grid(QwtPlot* plot);
};

#endif // GRID_H
