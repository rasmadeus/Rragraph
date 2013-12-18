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
    Curves* getCurves(int iFile);
    LegendItem* getLegend();
    void autoSize();
    void setExportSize(const QSizeF& size);
    const QSizeF& getExportSize() const;
    double axiStep(Axis axis) const;
Q_SIGNALS:
    void zoomed();
protected:
    void keyPressEvent(QKeyEvent* evt);
    void keyReleaseEvent(QKeyEvent* evt);
    void mouseDoubleClickEvent(QMouseEvent* evt);
private:
    Canvas* canvas;
    Grid* grid;
    LegendItem* legend;
    bool controlIsPressed;
    QSizeF exportSize;
};

#endif // PLOT_H