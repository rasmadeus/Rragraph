#ifndef PLOTSETTINGSVIEW_H
#define PLOTSETTINGSVIEW_H

class Plot;
class PlotSettings;
class QMdiSubWindow;
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
    void localeWasChanged();
public slots:
    void setOwner(QMdiSubWindow* window);
private:
    void addView(PlotSettings* view, const QString& title);
    Ui::PlotSettingsView* ui;
    Plot* owner;
    QList<PlotSettings*> views;
};

#endif // PLOTSETTINGSVIEW_H
