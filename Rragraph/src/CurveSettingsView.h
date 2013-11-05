#ifndef CURVESETTINGSVIEW_H
#define CURVESETTINGSVIEW_H

class CurvesModel;
class Plot;
class CurveSettings;
#include <QDialog>
#include "global.h"

namespace Ui {
class CurveSettingsView;
}

class CurveSettingsView : public QDialog
{
    Q_OBJECT
    SINGLETON_HEADER(CurveSettingsView, QWidget)
public:
    void setOwner(Plot* owner);
    ~CurveSettingsView();
    void localeWasChanged();
public slots:
    void show();
private:
    void setXYData(const QModelIndex& index);
    void setColorData(const QModelIndex& index);
    void setOtherData(const QModelIndex& index);
private slots:
    void wasRemovedAllFiles();
    void loadFiles();
    void reloadFile();
    void setCurves(const QModelIndex& index);
    void wasLoaded(int iFile);
    void removeSamples();
    void clickedToCurvesView(const QModelIndex& index);
private:
    Ui::CurveSettingsView* ui;
    CurvesModel* curvesModel;
    Plot* owner;
    CurveSettings* curveSettings;
};

#endif // CURVESETTINGSVIEW_H
