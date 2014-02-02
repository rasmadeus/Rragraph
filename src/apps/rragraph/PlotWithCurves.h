#ifndef PLOTWITHCURVES_H
#define PLOTWITHCURVES_H

class SamplesManager;
class CurvesManager;
class CurvesManagerView;
#include <Plot.h>

class PlotWithCurves : public Plot
{
    Q_OBJECT
public:
    PlotWithCurves(SamplesManager* samplesManager, CurvesManagerView *curvesManagerView, QWidget* parent = 0);
    ~PlotWithCurves();
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    CurvesManagerView* curvesManagerView;
    CurvesManager* curvesManager;
};

#endif // PLOTWITHCURVES_H
