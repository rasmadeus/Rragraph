#ifndef CURVESETTINGSVIEW_H
#define CURVESETTINGSVIEW_H

class CurvesModel;
class Plot;
class CurveSettings;
#include <QDialog>

namespace Ui {
class CurveSettingsView;
}

class CurveSettingsView : public QDialog
{
    Q_OBJECT
    static CurveSettingsView* instance ;
    Ui::CurveSettingsView* ui;
    CurvesModel* curvesModel;
    Plot* owner;
    CurveSettings* curveSettings;
    explicit CurveSettingsView(QWidget* parent = 0);
public:
    static CurveSettingsView* getInstance();
    static void create(QWidget* parent = 0);
    void setOwner(Plot* owner);
    ~CurveSettingsView();
public slots:
    void show();
private:
    void setXYData(const QModelIndex& index);
    void setColorData(const QModelIndex& index);
    void setOtherData(const QModelIndex& index);
private slots:
    void loadFiles();
    void reloadFile();
    void setCurves(const QModelIndex& index);
    void wasLoaded(int iFile);
    void removeSamples();
    void clickedToCurvesView(const QModelIndex& index);
};

#endif // CURVESETTINGSVIEW_H
