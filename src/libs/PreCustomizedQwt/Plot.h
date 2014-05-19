#ifndef PLOT_H
#define PLOT_H

class Canvas;
class Grid;
class Curves;
class Curve;
class LegendItem;
class QwtPlotRenderer;
class QPrinter;
class QwtPoint3D;
#include <qwt_plot.h>
#include <QVector>
#include <Path.h>
#include <qwt_point_3d.h>

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
    void exportToPng(QwtPlotRenderer& renderer, const QString& path);
    int getResolution() const;
    void setResolution(int resolution);
    static Path exportPath;
    void setZoomStack();
    void setZoomBase();
public Q_SLOTS:
    void exportToPng();
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
    int resolution;
    QwtPoint3D xBase;
    QwtPoint3D yBase;
};

#endif // PLOT_H
