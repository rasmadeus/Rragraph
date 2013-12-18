#include "Zoomer.h"

Zoomer::Zoomer(int xAxis, int yAxis, QWidget* canvas) :
    QwtPlotZoomer(xAxis, yAxis, canvas)
{
    setTrackerMode  (QwtPicker::AlwaysOff);
    setRubberBand   (QwtPicker::NoRubberBand);
    setMousePattern (QwtEventPattern::MouseSelect3, Qt::MidButton); //Get the previous scale.
    setMousePattern (QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier); //Get the base scale.
    setRubberBand   (QwtPicker::RectRubberBand);
    setRubberBandPen(QPen(Qt::black));
    setTrackerMode  (QwtPicker::ActiveOnly);
    setTrackerPen   (QPen(Qt::black));
}
