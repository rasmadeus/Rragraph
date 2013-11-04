#ifndef PLOT_H
#define PLOT_H

class Canvas;
class Grid;
class Curves;
class Curve;
class LegendItem;
#include "global.h"
#include <qwt_plot.h>
#include <QHash>
#include "Savable.h"

class Plot : public QwtPlot, public Savable
{
    Q_OBJECT
    Canvas* canvas;
    Grid* grid;
    LegendItem* legend;
    QHash<int, Curves*> samples;
    bool controlIsPressed;
    QSizeF exportSize;
public:
    explicit Plot(QWidget* parent = 0);
    ~Plot();
    Curves* getCurves(int iFile);
    LegendItem* getLegend();
    void autoSize();
    void setExportSize(const QSizeF& size);
    const QSizeF& getExportSize() const;
    double axiStep(Axis axis) const;
    QJsonObject serialize() const;
    void restore(const QJsonObject& obj);
signals:
    void zoomed();
protected:
    void mousePressEvent(QMouseEvent* evt);
    void keyPressEvent(QKeyEvent* evt);
    void keyReleaseEvent(QKeyEvent* evt);
    void mouseDoubleClickEvent(QMouseEvent* evt);
private slots:
    void wasAdded(int iFile);
    void wasRemoved(int iFile);
};

#endif // PLOT_H
