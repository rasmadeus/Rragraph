#ifndef CURVES_H
#define CURVES_H

class Curve;
class Plot;
#include <QColor>
#include <QHash>

class Curves
{
public:
    Curves(int iFile, Plot* owner);
    ~Curves();
    Curve* getCurve(int i) const;
    void wasRemoved();
    int rowCount() const;
    void setX(int i);
    void setY(int i);
    void setColor(int i, const QColor& color);
    void setScale(int i, double scale);
    void setWidth(int i, int width);
    void setAbscissAddend(int i, double add);
    void setOrdinateAddend(int i, double add);
    void setSymbolStep(int i, int step);
    void setSymbolStyle(int i, int style);
    void update(int i);
    const QString& getHeader(int i) const;
    bool isX(int i) const;
    bool isY(int i) const;
    bool isLoading() const;
    void wasLoaded(int iFile);
    void headerWasChanged(int iFile, int i, const QString& header);
    void ifSetY(int i);
    void serialize(QJsonObject& plot) const;
    void restore(const QJsonObject& plot);
private:
    void resamples();
    void insertNewCurve(int i);
    void ifReplotOwner();
    void setSamples(int i, Curve* curve = nullptr);
    int iFile ;
    int iX;
    Plot* owner;
    QHash<int, Curve*> curves;
};

#endif // CURVES_H
