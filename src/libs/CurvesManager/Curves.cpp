#include "Curves.h"

Curves::Curves(Plot* owner, const Samples* samples):
    iX(0),
    owner(owner),
    samples(samples)
{
}

Curves::~Curves()
{
    clear();
}

bool Curves::isX(int i) const
{
    return iX == i;
}

#include <Curve.h>
bool Curves::isY(int i) const
{
    return curves.contains(i) && curves.value(i)->isVisible();
}

#include <Samples.h>
#include <Plot.h>
void Curves::resamples()
{
    if(iX >= samples->count()){
        clear();
        return;
    }
    foreach(int iY, curves.keys()){
        if(iY >= samples->count()){
            delete curves.take(iY);
        }
        else{
            setSamplesForCurve(iY);
            updateCurveTitle(iY);
        }
    }
    owner->replot();
}

void Curves::setSamplesForCurve(int iY)
{
    Curve* curve = curves.value(iY);
    curve->setSamples(samples->getProxyColumn(iX), samples->getProxyColumn(iY));
}

void Curves::clear()
{
    qDeleteAll(curves);
    iX = 0;
    owner->replot();
}

int Curves::count() const
{
   return curves.count();
}

void Curves::setX(int iX)
{
    if(!isX(iX)){
        this->iX = iX;
        resamples();
    }
}

Plot* Curves::getOwner() const
{
    return owner;
}

void Curves::setY(int iY)
{
    if(curves.contains(iY)){
        Curve* curve = curves.value(iY);
        if(curve->isVisible()){
            curve->detach();
            curve->setVisible(false);
        }
        else{
            curve->setVisible(true);
            curve->attach(owner);
        }
    }
    else{
        Curve* curve = new Curve(samples->getProxyHeader(iY));
        curves[iY] = curve;
        setSamplesForCurve(iY);
        curve->attach(owner);
    }
    owner->replot();
}

Curve* Curves::getCurve(int iY) const
{
    return curves.value(iY);
}

#include <QModelIndex>
Curve* Curves::getCurve(const QModelIndex& consecutiveIndex) const
{
    return getCurveFrom(consecutiveIndex.row());
}

Curve* Curves::getCurveFrom(int consecutiveIndex) const
{
    const int iY = getCurvesKeys().at(consecutiveIndex);
    return getCurve(iY);
}

QList<int> Curves::getCurvesKeys() const
{
    return curves.keys();
}

const Samples* Curves::getSamples() const
{
    return samples;
}

void Curves::updateCurveTitle(int iY)
{
    Curve* curve = curves.value(iY);
    curve->setTitle(samples->getProxyHeader(iY));
}
