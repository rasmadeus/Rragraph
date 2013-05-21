#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include "../../qwt-6.0.1/qwt_plot_curve.h"
#include <QList>

class PlotCurve : public QwtPlotCurve{
private:
    void init();
public:
    explicit PlotCurve(QString name);
    ~PlotCurve();
    PlotCurve(QString name, QString style, const QVector<double>& x, const QVector<double>& y);
    void setStyle(QString key); //The style set the pens for curve.
    void reloadStyle();
    static void updateStyles();
private:
    static QList<PlotCurve*> plotCurves;
    QString styleCurve;
};

#endif // PLOTCURVE_H
