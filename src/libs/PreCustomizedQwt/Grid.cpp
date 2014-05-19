#include "Grid.h"

Grid::Grid(QwtPlot* plot):
    QwtPlotGrid()
{
    static QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidthF(0.5);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setDashPattern(QVector<qreal>() << 4 << 4);
    setMajorPen(pen);
    setMinorPen(pen);
    attach(plot);
}
