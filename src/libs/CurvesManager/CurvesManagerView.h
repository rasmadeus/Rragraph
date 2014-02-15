#ifndef CURVESMANAGERVIEW_H
#define CURVESMANAGERVIEW_H

class Samples;
class SamplesManager;
class SamplesManagerView;
class CurvesFiller;
class CurvesSettings;
class CurvesManager;
#include <QDialog>

namespace Ui {
class CurvesManagerView;
}

class CurvesManagerView : public QDialog
{
    Q_OBJECT
public:
    explicit CurvesManagerView(SamplesManager* samplesManager, QWidget* parent = 0);
    ~CurvesManagerView();
    void setCurvesManager(CurvesManager* curvesManager);
Q_SIGNALS:
    void wasChoosen(const Samples* samples);
private slots:
    void setCurvesToFiller(int i);
    void setSamplesPathToWindowTitle(int i);
    void setRawWindowTitle();
    void updateCurvesToFiller(int i);
    void curvesFillerToNullData();
private:
    void saveSettings();
    void restoreSettings();
    void createCurvesFiller();
    void createCurvesSettings();
    void createSamplesManagerView();
    Ui::CurvesManagerView *ui;
    SamplesManagerView* samplesManagerView;
    CurvesFiller* curvesFiller;
    CurvesSettings* curvesSettings;
    CurvesManager* curvesManager;
    SamplesManager* samplesManager;
};

#endif // CURVESMANAGERVIEW_H
