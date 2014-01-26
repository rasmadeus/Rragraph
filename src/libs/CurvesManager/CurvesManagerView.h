#ifndef CURVESMANAGERVIEW_H
#define CURVESMANAGERVIEW_H

class Samples;
class CurvesManager;
class SamplesManagerView;
class CurvesFiller;
class CurvesSettings;
#include <QWidget>

namespace Ui {
class CurvesManagerView;
}

class CurvesManagerView : public QWidget
{
    Q_OBJECT
public:
    explicit CurvesManagerView(QWidget *parent = 0);
    ~CurvesManagerView();
    void setCurvesManager(CurvesManager* curvesManager);
Q_SIGNALS:
    void wasChoosen(Samples* samples);
private slots:
    void setCurvesToFiller(int i);
private:
    SamplesManagerView* samplesManagerView;
    CurvesFiller* curvesFiller;
    CurvesSettings* curvesSettings;
    CurvesManager* curvesManager;
    Ui::CurvesManagerView *ui;
};

#endif // CURVESMANAGERVIEW_H
