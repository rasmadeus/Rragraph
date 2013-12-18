#ifndef CURVESETTINGS_H
#define CURVESETTINGS_H

class Curve;
class Curves;
#include <QDialog>

namespace Ui {
class CurveSettings;
}

class CurveSettings : public QDialog
{
    Q_OBJECT
public:
    explicit CurveSettings(QWidget *parent = 0);
    ~CurveSettings();
    void setModel(Curves* curves, int row);
    void localeWasChanged();
private slots:
    void setWidth(int width);
    void setScale(double scale);
    void setAddendX(double add);
    void setAddendY(double add);
    void turnSymbol(bool on);
    void setSymbolStyle(int i);
    void setStep(int step);
    void setColor();
    void setDushPattern();
private:
    Ui::CurveSettings* ui;
    Curve* curve;
    Curves* curves;
    int row;
};

#endif // CURVESETTINGS_H
