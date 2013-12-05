#include "PlotSettingsView.h"
#include "ui_PlotSettingsView.h"
#include "Plot.h"
#include "HeadersView.h"
#include "Axes.h"
#include "LegendSettings.h"
#include "ExportSettings.h"
#include "Translator.h"
#include "CommonPlotSettings.h"
PlotSettingsView::PlotSettingsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotSettingsView),
    owner(nullptr)
{
    ui->setupUi(this);

    addView(new Axes(ui->toolBox),               tr("Axes"));
    addView(new CommonPlotSettings(ui->toolBox), tr("Common property"));
    addView(new LegendSettings(ui->toolBox),     tr("Legend"));
    addView(new ExportSettings(ui->toolBox),     tr("Export"));
}

PlotSettingsView::~PlotSettingsView(){
    delete ui;
}

void PlotSettingsView::localeWasChanged()
{
    ui->toolBox->setItemText(0, tr("Axes"));
    ui->toolBox->setItemText(1, tr("Common property"));
    ui->toolBox->setItemText(2, tr("Legend"));
    ui->toolBox->setItemText(3, tr("Export"));
    foreach (PlotSettings* plotSettings, views) {
        plotSettings->localeWasChanged();
    }
}

void PlotSettingsView::addView(PlotSettings* view, const QString& title)
{
    views << view;
    ui->toolBox->addItem(view, title);   
}

#include <QMdiSubWindow>
void PlotSettingsView::setOwner(QMdiSubWindow* window)
{    
    owner = window ? static_cast<Plot*>(window->widget()) : nullptr;
    foreach (PlotSettings* view, views) {
       view->setOwner(owner);
    }
}
