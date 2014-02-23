#ifndef CURVESETTINGS_H
#define CURVESETTINGS_H

class Plot;
class Curves;
#include <QWidget>

namespace Ui {
class CurveSettings;
}

class Curve;

class CurveSettings : public QWidget
{
    Q_OBJECT
public:
    explicit CurveSettings(QWidget *parent = 0);
    ~CurveSettings();
    void setCurve(Curves* curves, Curve* curve);
    void retranslate();
Q_SIGNALS:
    void visibilityCurveChanged();
protected:
    bool eventFilter(QObject* obj, QEvent* evt);
private slots:
    void setCurveColor();
    void setCurveWidth(int width);
    void setCurveVisible(bool clicked);
    void setSymbolStyle(int i);
    void setCurveDashPattern(const QString& dashPattern);
    void setAddendX(double addend);
    void setAddendY(double addend);
    void setMultY(double mult);
private:
    void setDataFromCurve();
    void restore();
    void fillSymbol();
    Ui::CurveSettings *ui;
    Curve* curve;
    Plot* owner;
    Curves* curves;
};

#endif // CURVESETTINGS_H
