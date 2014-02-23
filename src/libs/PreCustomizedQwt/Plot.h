#ifndef PLOT_H
#define PLOT_H

class Canvas;
class Grid;
class Curves;
class Curve;
class LegendItem;

#include <qwt_plot.h>
#include <QVector>

class Plot : public QwtPlot
{
    Q_OBJECT
public:
    explicit Plot(QWidget* parent = 0);
    ~Plot();
    LegendItem* getLegend();
    void autoscale();
    void setExportSize(const QSizeF& size);
    const QSizeF& getExportSize() const;
    double axisStep(Axis axis) const;
Q_SIGNALS:
    void zoomed();
protected:
    void keyPressEvent(QKeyEvent* evt);
    void keyReleaseEvent(QKeyEvent* evt);
    void mouseDoubleClickEvent(QMouseEvent* evt);
    bool controlIsPressed;
    Canvas* canvas;
    Grid* grid;
    LegendItem* legend;
    QSizeF exportSize;
};

#endif // PLOT_H
