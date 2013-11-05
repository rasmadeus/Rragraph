#ifndef PLOT_H
#define PLOT_H

class Canvas;
class Grid;
class Curves;
class Curve;
class LegendItem;
#include "global.h"
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
    void serialize(QJsonArray& plots) const;
    void restore(const QJsonValue& value);
    void serializeCurves(QJsonArray& plots) const;
    void restoreCurves(int iFile, const QJsonObject& plot);
    bool isCurvesRestoring() const;
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
    void headerWasChanged(int iFile, int i, const QString& header);
private:
    Canvas* canvas;
    Grid* grid;
    LegendItem* legend;
    QVector<Curves*> curves;
    bool controlIsPressed;
    QSizeF exportSize;
    bool curvesIsRestoring;
};

#endif // PLOT_H
