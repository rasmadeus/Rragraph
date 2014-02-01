#include "PlotWithCurves.h"

#include <CurvesManager.h>
PlotWithCurves::PlotWithCurves(SamplesManager* samplesManager, CurvesCustomizer* curvesCustomizer, QWidget* parent) :
    Plot(parent),
    curvesCustomizer(curvesCustomizer)
{
    curvesManager = new CurvesManager(samplesManager, this);
}

PlotWithCurves::~PlotWithCurves()
{
    delete curvesManager;
}

#include "CurvesCustomizer.h"
#include <CurvesManagerView.h>
#include <QMouseEvent>
void PlotWithCurves::mousePressEvent(QMouseEvent* event)
{
    if(!controlIsPressed && event->button() == Qt::RightButton){
        curvesCustomizer->getCurvesManagerView()->setCurvesManager(curvesManager);
        curvesCustomizer->show();
    }
    Plot::mousePressEvent(event);
}
