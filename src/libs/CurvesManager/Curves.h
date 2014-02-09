#ifndef CURVES_H
#define CURVES_H

class Plot;
class Samples;
class Curve;
class QModelIndex;
#include <QHash>

class Curves
{
public:
    Curves(Plot* owner, const Samples* samples);
    ~Curves();
    void resamples();
    void setX(int iX);
    void setY(int iY);
    bool isX(int i) const;
    bool isY(int i) const;
    Curve* getCurve(int iY) const;
    Curve* getCurve(const QModelIndex& consecutiveIndex) const;
    Curve* getCurveFrom(int consecutiveIndex) const;
    QList<int> getCurvesKeys() const;
    const Samples* getSamples() const;
    void clear();
    int count() const;
    Plot* getOwner() const;
private:
    void setSamplesForCurve(int iY);
    void updateCurveTitle(int iY);
    int iX;
    Plot* owner;
    const Samples* samples;
    QHash<int, Curve*> curves;
};

#endif // CURVES_H
