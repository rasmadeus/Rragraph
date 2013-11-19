#include "Curves.h"

Curves::Curves(int iFile, Plot* owner):
    iFile(iFile),
    iX(0),
    owner(owner)
{    
}

#include "Curve.h"
#include "Plot.h"
Curves::~Curves(){
    qDeleteAll(curves);
}

Curve* Curves::getCurve(int i) const{
    return curves.value(i, nullptr);
}

#include "Files.h"
int Curves::rowCount() const{
    return Files::getInstance()->countSamples(iFile);
}

void Curves::update(int i){
    setSamples(i);
}

#include "HeaderSamples.h"
const QString& Curves::getHeader(int i) const{
    return HeaderSamples::getInstance()->getHeader(iFile, i);
}

bool Curves::isX(int i) const{
    return i == iX;
}
bool Curves::isY(int i) const{
    return curves.contains(i) ? curves.value(i)->isVisible() : false;
}

bool Curves::isLoading() const{
    return Files::getInstance()->isLoading(iFile);
}

void Curves::setX(int i)
{
    if(i != iX){
        iX = i;
        resamples();
    }
}

void Curves::wasRemoved(){
    --iFile;
}

void Curves::wasLoaded(int iFile)
{
    if(this->iFile == iFile){
        const int nColumns = Files::getInstance()->countSamples(iFile);
        foreach(int key, curves.keys()){
            if(key >= nColumns){
                delete curves.take(key);
            }
        }
        resamples();
    }
}

void Curves::headerWasChanged(int iFile, int i, const QString& header)
{
    if(this->iFile == iFile && curves.contains(i)){
        curves.value(i)->setTitle(header);
        owner->replot();
    }
}

void Curves::setSamples(int i, Curve* curve)
{
    if(!curve){
        curve = curves.value(i);
    }
    Files* files = Files::getInstance();
    curve->setSamples(files->getSamples(iFile, iX), files->getSamples(iFile, i));
    curve->attach(owner);
}

void Curves::insertNewCurve(int i)
{
    const QString header = HeaderSamples::getInstance()->getHeader(iFile, i);
    Curve* curve = new Curve(header);
    curve->setPen(QPen(QColor(qrand() % 255, qrand() % 255, qrand() % 255)));
    curves[i] = curve;
    setSamples(i, curve);
}

void Curves::setY(int i)
{
    if(curves.contains(i)){
        Curve* curve = curves.value(i);
        if(curve->isVisible()){
            curve->setVisible(false);
            curve->detach();
        }
        else{
            curve->setVisible(true);
            curve->attach(owner);
        }
    }
    else{
        insertNewCurve(i);
    }
    ifReplotOwner();
}

void Curves::ifReplotOwner()
{
    if(owner->isCurvesRestoring()){
        owner->replot();
        return;
    }
    int countAbilityCurves = 0;
    foreach (Curve* curve, curves) {
        if(curve->isVisible()){
            ++countAbilityCurves;
        }
        if(countAbilityCurves > 1){
            owner->replot();
            return;
        }
    }
    owner->autoSize();
}

void Curves::ifSetY(int i)
{
    if(!isY(i)){
        setY(i);
    }
}

void Curves::setColor(int i, const QColor& color)
{
    ifSetY(i);
    Curve* curve = curves.value(i);
    QPen pen = curve->pen();
    pen.setColor(color);
    curve->setPen(pen);
    curve->setSymbolStyle(curve->getSymbolStyle());
    owner->replot();
}

void Curves::setScale(int i, double scale)
{
    ifSetY(i);
    Curve* curve = curves.value(i);
    curve->setMultY(scale);
    setSamples(i, curve);
    owner->replot();
}

#include <qwt_symbol.h>
void Curves::setWidth(int i, int width)
{
    ifSetY(i);
    Curve* curve = curves.value(i);
    QPen pen = curve->pen();
    pen.setWidth(width);
    curve->setPen(pen);
    curve->setSymbolStyle(curve->getSymbolStyle());
    owner->replot();
}

void Curves::setAbscissAddend(int i, double add)
{
   ifSetY(i);
   Curve* curve = curves.value(i);
   curve->setAddendX(add);
   setSamples(i, curve);
   owner->replot();
}

void Curves::setOrdinateAddend(int i, double add)
{
    ifSetY(i);
    Curve* curve = curves.value(i);
    curve->setAddendY(add);
    setSamples(i, curve);
    owner->replot();
}

void Curves::setSymbolStep(int i, int step)
{
    ifSetY(i);
    Curve* curve = curves.value(i);
    curve->setStep(step);
    owner->replot();
}

void Curves::setSymbolStyle(int i, int style)
{
    ifSetY(i);
    Curve* curve = curves.value(i);
    curve->setSymbolStyle(style);
    owner->replot();
}

void Curves::resamples()
{
    Files* files = Files::getInstance();
    foreach(int i, curves.keys()){
        curves.value(i)->setSamples(
            files->getSamples(iFile, iX),
            files->getSamples(iFile, i)
        );
    }
    owner->replot();
}

#include <QJsonArray>
#include <QJsonObject>
void Curves::serialize(QJsonObject& plot) const
{
    QJsonObject curves;
    curves["absciss"] = iX;
    QJsonArray ordinates;
    foreach(int iY, this->curves.keys()){
        QJsonObject curve;
        curve["curveIndex"] = iY;
        this->curves.value(iY)->serialize(curve);
        ordinates.push_back(curve);
    }
    curves["ordinates"] = ordinates;
    plot["curves"] = curves;
}

void Curves::restore(const QJsonObject& plot)
{
    const QJsonObject curves = plot.value("curves").toObject();
    const int iX = curves.value("absciss").toVariant().toInt();
    if(Files::getInstance()->isOutOfRange(iFile, iX)){
        return;
    }
    setX(iX);
    foreach(const QJsonValue& y, curves.value("ordinates").toArray()){
        const QJsonObject curve = y.toObject();
        const int iY = curve.value("curveIndex").toVariant().toInt();
        if(Files::getInstance()->isOutOfRange(iFile, iY)){
            return;
        }
        setY(iY);
        this->curves.value(iY)->restore(curve);
    }
}
