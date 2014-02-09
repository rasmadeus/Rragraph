#include "LegendPlotSettings.h"
#include "ui_LegendPlotSettings.h"

LegendPlotSettings::LegendPlotSettings(QWidget *parent) :
    PlotSettings(parent),
    ui(new Ui::LegendPlotSettings)
{
    ui->setupUi(this);
    fillPos();
    ui->settingsGroup->setFocusPolicy(Qt::NoFocus);
    connect(ui->copy, SIGNAL(clicked()), SIGNAL(dublicateSettings()));
    connect(ui->settingsGroup, SIGNAL(toggled(bool)), SLOT(turnLegend(bool)));
    connect(ui->font, SIGNAL(clicked()), SLOT(setFont()));
    connect(ui->opacity, SIGNAL(valueChanged(int)), SLOT(setOpacity(int)));
    connect(ui->columnsCount, SIGNAL(valueChanged(int)), SLOT(setMaximumColumns(int)));
    connect(ui->horPos, SIGNAL(activated(int)), SLOT(setPos()));
    connect(ui->verPos, SIGNAL(activated(int)), SLOT(setPos()));
}

LegendPlotSettings::~LegendPlotSettings()
{
    delete ui;
}

#include <Plot.h>
#include <LegendItem.h>
void LegendPlotSettings::copySettingsTo(Plot* plot)
{
    LegendItem* legend = plot->getLegend();
    legend->setVisible(ui->settingsGroup->isChecked());
    legend->setFont(this->plot->getLegend()->font());
    legend->setMaxColumns(ui->columnsCount->value());
    legend->setBackgroundOpacity(ui->opacity->value());
    updatePos(plot);
    plot->replot();
}

void LegendPlotSettings::fillFromPlot()
{
    LegendItem* legend = plot->getLegend();
    {
        ui->settingsGroup->setChecked(legend->isVisible());
        ui->opacity->setValue(legend->backgroundBrush().color().alpha());
        ui->columnsCount->setValue(legend->maxColumns());
    }
    {
        const Qt::Alignment flags = plot->getLegend()->alignment();
        ui->horPos->setCurrentIndex(
           flags.testFlag(Qt::AlignLeft) ? 0 : flags.testFlag(Qt::AlignHCenter) ? 1 : 2
        );
        ui->verPos->setCurrentIndex(
           flags.testFlag(Qt::AlignTop)  ? 0 : flags.testFlag(Qt::AlignVCenter) ? 1 : 2
        );
    }
}

void LegendPlotSettings::fillPos()
{
    {
        ui->horPos->addItem(tr("Left"), Qt::AlignLeft);
        ui->horPos->addItem(tr("Center"), Qt::AlignHCenter);
        ui->horPos->addItem(tr("Right"),  Qt::AlignRight);
    }
    {
        ui->verPos->addItem(tr("Top"),    Qt::AlignTop);
        ui->verPos->addItem(tr("Center"), Qt::AlignVCenter);
        ui->verPos->addItem(tr("Bottom"), Qt::AlignBottom);
    }
}

void LegendPlotSettings::turnLegend(bool on)
{
    plot->getLegend()->setVisible(on);
    plot->replot();
}

#include <QFontDialog>
void LegendPlotSettings::setFont()
{
    emit catchPlot();
    bool ok;    
    QFont font = QFontDialog::getFont(&ok, plot->getLegend()->font(), this, tr("Set legend font"));
    if(ok){
        plot->getLegend()->setFont(font);
        plot->replot();
    }
    emit freePlot();
}

void LegendPlotSettings::setOpacity(int opacity)
{
    plot->getLegend()->setBackgroundOpacity(opacity);
    plot->replot();
}

void LegendPlotSettings::setMaximumColumns(int count)
{
    plot->getLegend()->setMaxColumns(count);
    plot->replot();
}

void LegendPlotSettings::updatePos(Plot* plot)
{
    plot->getLegend()->setAlignment(
        Qt::AlignmentFlag(ui->horPos->itemData(ui->horPos->currentIndex()).toInt()) |
        Qt::AlignmentFlag(ui->verPos->itemData(ui->verPos->currentIndex()).toInt())
    );
}

void LegendPlotSettings::setPos()
{
    updatePos(plot);
    plot->replot();
}
