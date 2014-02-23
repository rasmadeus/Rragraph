#ifndef PLOTWITHCURVES_H
#define PLOTWITHCURVES_H

class SamplesManager;
class CurvesManager;
class CurvesManagerView;
class CurveProCreator;
#include <Plot.h>

class PlotWithCurves : public Plot
{
    Q_OBJECT
public:
    PlotWithCurves(SamplesManager* samplesManager, CurvesManagerView* curvesManagerView, QWidget* parent = 0);
    ~PlotWithCurves();
    void serialize(QJsonArray& plots) const;
    void restore(const QJsonObject& plotSettings);
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    void serializeAxis(Axis axis, const QString& prefix, QJsonObject& plotSettings) const;
    void restoreAxis(Axis axis, const QString& prefix, const QJsonObject& plotSettings);
    CurvesManagerView* curvesManagerView;
    CurvesManager* curvesManager;
};

#endif // PLOTWITHCURVES_H
