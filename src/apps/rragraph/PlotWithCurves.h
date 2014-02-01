#ifndef PLOTWITHCURVES_H
#define PLOTWITHCURVES_H

class SamplesManager;
class CurvesManager;
class CurvesCustomizer;
#include <Plot.h>

class PlotWithCurves : public Plot
{
    Q_OBJECT
public:
    PlotWithCurves(SamplesManager* samplesManager, CurvesCustomizer* curvesCustomizer, QWidget* parent = 0);
    ~PlotWithCurves();
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    CurvesCustomizer* curvesCustomizer;
    CurvesManager* curvesManager;
};

#endif // PLOTWITHCURVES_H
