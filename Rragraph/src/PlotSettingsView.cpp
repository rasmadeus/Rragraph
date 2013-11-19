#include "PlotSettingsView.h"
#include "ui_PlotSettingsView.h"
#include "Plot.h"
#include "HeadersView.h"
#include "AxisPlotSettings.h"
#include "LegendSettings.h"
#include "ExportSettings.h"
#include "Translator.h"
PlotSettingsView::PlotSettingsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotSettingsView),
    owner(nullptr)
{
    ui->setupUi(this);

    addView(new AxisPlotSettings(QwtPlot::xBottom, ui->toolBox), tr("Absciss"));
    addView(new AxisPlotSettings(QwtPlot::yLeft, ui->toolBox), tr("Ordinate"));
    addView(new LegendSettings(ui->toolBox), tr("Legend"));
    addView(new ExportSettings(ui->toolBox), tr("Export"));
}

PlotSettingsView::~PlotSettingsView(){
    delete ui;
}

void PlotSettingsView::localeWasChanged()
{
    ui->toolBox->setItemText(0, tr("Absciss"));
    ui->toolBox->setItemText(1, tr("Ordinate"));
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
