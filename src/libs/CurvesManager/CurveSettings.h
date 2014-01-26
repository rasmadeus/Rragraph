#ifndef CURVESETTINGS_H
#define CURVESETTINGS_H

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
    void setCurve(Curve* curve);
protected:
    bool eventFilter(QObject* obj, QEvent* evt);
private slots:
    void setCurveColor();
    void setCurveWidth(int width);
    void setCurveVisible(bool clicked);
    void setSymbolStyle(int i);
    void setCurveDashPattern(const QString& dashPattern);
private:
    void setDataFromCurve();
    void restore();
    void fillSymbol();
    Ui::CurveSettings *ui;
    Curve* curve;
};

#endif // CURVESETTINGS_H
