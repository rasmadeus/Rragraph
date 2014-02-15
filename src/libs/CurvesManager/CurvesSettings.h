#ifndef CURVESSETTINGS_H
#define CURVESSETTINGS_H

class Curves;
class CurvesModel;
class CurveSettings;
#include <QWidget>

namespace Ui {
class CurvesSettings;
}

class CurvesSettings : public QWidget
{
    Q_OBJECT
public:
    explicit CurvesSettings(QWidget *parent = 0);
    ~CurvesSettings();
    void setCurves(Curves* curves);
Q_SIGNALS:
    void visibilityCurveChanged();
public slots:
    void resetView();
private slots:
    void setCurveSettings();
private:
    Ui::CurvesSettings *ui;
    CurveSettings* curveSettings;
    CurvesModel* curvesModel;
};

#endif // CURVESSETTINGS_H
