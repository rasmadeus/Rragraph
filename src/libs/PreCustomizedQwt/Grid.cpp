#include "Grid.h"

Grid::Grid(QwtPlot* plot):
    QwtPlotGrid()
{
    setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    setMinorPen(QPen(Qt::gray, 0, Qt::DotLine));
    attach(plot);
}
