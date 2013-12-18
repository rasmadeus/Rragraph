#ifndef CURVE_H
#define CURVE_H

#include <qwt_plot_curve.h>

class Curve : public QwtPlotCurve
{
public:
    Curve(const QString& name);
    void setStep(int step);
    int getStep() const;
    void setAddendY(double addend);
    double getAddendY() const;
    void setAddendX(double addend);
    double getAddendX() const;
    void setMultY(double mult);
    double getMultY() const;
    void setSamples(const QVector<double>& xData, const QVector<double>& yData);
    int getSymbolStyle() const;
    void setSymbolStyle(int style);
    void serialize(QJsonObject& curves) const;
    void restore(const QJsonObject& curves);
    static QPen fillPenWithDashPattern(const QPen& src, const QString& dashes);
    static QString fromPenDashPattern(const QPen& pen);
protected:
    void drawSymbols(
        QPainter* painter,
        const QwtSymbol& symbol,
        const QwtScaleMap& xMap,
        const QwtScaleMap& yMap,
        const QRectF& canvasRect,
        int from,
        int to
    ) const;
    int step;
    double addendY;
    double addendX;
    double multY;
    int symbolStyle;
};

#endif // CURVE_H
