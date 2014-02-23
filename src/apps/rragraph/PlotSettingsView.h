#ifndef PLOTSETTINGSVIEW_H
#define PLOTSETTINGSVIEW_H

class PlotSettings;
class QMdiSubWindow;
class Group;
class GroupSettings;
#include "PlotWithCurves.h"
#include <QList>
#include <QWidget>

namespace Ui {
class PlotSettingsView;
}

class PlotSettingsView : public QWidget
{
    Q_OBJECT
public:
    explicit PlotSettingsView(QWidget *parent = 0);
    ~PlotSettingsView();
public slots:
    void catchAndTorturePlot(QMdiSubWindow* window);
    void catchAndTortureGroup(Group* group);
    void freeGroup();
    void lockPlot();
    void unlockPlot();
    void retraslate();
signals:
    void groupNameWasChanged();
private slots:
    void dublicateSettingsToGroup(PlotSettings* plotSettings);
private:
    void toNewState(QMdiSubWindow* window);
    void toDefaultState();
    void createSettingsWidgets();
    void addSettingsWidgetToForm();
    void listenSettingsWidget();
    void createGroupSettings();
    Ui::PlotSettingsView* ui;
    PlotWithCurves* plot;
    QList<PlotSettings*> settings;
    bool catchAble;
    Group* group;
    GroupSettings* groupSettings;
};

#endif // PLOTSETTINGSVIEW_H
