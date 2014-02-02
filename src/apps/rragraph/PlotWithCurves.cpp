#include "PlotWithCurves.h"

#include <CurvesManager.h>
PlotWithCurves::PlotWithCurves(SamplesManager* samplesManager, CurvesManagerView* curvesManagerView, QWidget* parent) :
    Plot(parent),
    curvesManagerView(curvesManagerView)
{
    curvesManager = new CurvesManager(samplesManager, this);
}

PlotWithCurves::~PlotWithCurves()
{
    delete curvesManager;
}

#include <CurvesManagerView.h>
#include <CurvesManagerView.h>
#include <QMouseEvent>
void PlotWithCurves::mousePressEvent(QMouseEvent* event)
{
    if(!controlIsPressed && event->button() == Qt::RightButton){
        curvesManagerView->setCurvesManager(curvesManager);
        curvesManagerView->show();
    }
    Plot::mousePressEvent(event);
}
