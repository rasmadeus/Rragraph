#include "PlotSettings.h"
#include "ui_PlotSettings.h"

PlotSettings::PlotSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotSettings),
    plot(nullptr)
{
    ui->setupUi(this);
    createLookAndFeel();
    routeActions();
}

PlotSettings::~PlotSettings()
{
    delete ui;
}

#include <QColorDialog>
#include <qwt_text.h>
static auto fillWithColor = [](QWidget* parent, QwtText& qwtText)
{
    QColor color = QColorDialog::getColor(qwtText.color(), parent, QT_TRANSLATE_NOOP("PlotSettings", "Set plot title color"));
    if(color.isValid()){
        qwtText.setColor(color);
    }
};

#include <QFontDialog>
static auto fillWithFont = [](QWidget* parent, QwtText& qwtText)
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, qwtText.font(), parent, QT_TRANSLATE_NOOP("PlotSettings", "Set plot title font"));
    if(ok){
        qwtText.setFont(font);
    }
};

#include "Plot.h"
void PlotSettings::setTitle(const QString& title)
{
    plot->setTitle(title);
}

void PlotSettings::setTitleColor()
{
    fillPlotTitle(fillWithColor);
}

void PlotSettings::setTitleFont()
{
    fillPlotTitle(fillWithFont);
}

void PlotSettings::fillPlotTitle(const std::function<void (QWidget*, QwtText&)>& filler)
{
    QwtText title = plot->title();
    filler(this, title);
    plot->setTitle(title);
}

void PlotSettings::routeActions()
{
    connect(ui->plotTitleColor,   SIGNAL(clicked()),            SLOT(setTitleColor()));
    connect(ui->plotTitleFont,    SIGNAL(clicked()),            SLOT(setTitleFont()));
    connect(ui->legendFont,       SIGNAL(clicked()),            SLOT(setLegendFont()));
    connect(ui->printPlot,        SIGNAL(clicked()),            SLOT(printCurrentPlot()));
    connect(ui->savePlotToImage,  SIGNAL(clicked()),            SLOT(savePlotToImage()));
    connect(ui->xColor,           SIGNAL(clicked()),            SLOT(setTitleColorX()));
    connect(ui->xFont,            SIGNAL(clicked()),            SLOT(setTitleFontX()));
    connect(ui->yColor,           SIGNAL(clicked()),            SLOT(setTitleColorY()));
    connect(ui->yFont,            SIGNAL(clicked()),            SLOT(setTitleFontY()));
    connect(ui->settingsGroup,    SIGNAL(toggled(bool)),        SLOT(turnLegend(bool)));
    connect(ui->horPos,           SIGNAL(activated(int)),       SLOT(setLegendPos()));
    connect(ui->verPos,           SIGNAL(activated(int)),       SLOT(setLegendPos()));
    connect(ui->copyExport,       SIGNAL(clicked()),            SLOT(copyExport()));
    connect(ui->copyLegend,       SIGNAL(clicked()),            SLOT(copyLegend()));
    connect(ui->copyPlotTitle,    SIGNAL(clicked()),            SLOT(copyPlotTitle()));
    connect(ui->copyX,            SIGNAL(clicked()),            SLOT(copyX()));
    connect(ui->copyY,            SIGNAL(clicked()),            SLOT(copyY()));
    connect(ui->plotTitle,        SIGNAL(textChanged(QString)), SLOT(setTitle(QString)));
    connect(ui->opacity,          SIGNAL(valueChanged(int)),    SLOT(setLegendOpacity(int)));
    connect(ui->columnsCount,     SIGNAL(valueChanged(int)),    SLOT(setLegendMaxColumns(int)));
    connect(ui->plotExportHeight, SIGNAL(valueChanged(int)),    SLOT(setExportSize()));
    connect(ui->plotExportWidth,  SIGNAL(valueChanged(int)),    SLOT(setExportSize()));
    connect(ui->xMin,             SIGNAL(valueChanged(double)), SLOT(updateScaleX()));
    connect(ui->xMax,             SIGNAL(valueChanged(double)), SLOT(updateScaleX()));
    connect(ui->xStep,            SIGNAL(valueChanged(double)), SLOT(updateScaleX()));
    connect(ui->xTitle,           SIGNAL(textChanged(QString)), SLOT(setTitleX()));
    connect(ui->yMin,             SIGNAL(valueChanged(double)), SLOT(updateScaleY()));
    connect(ui->yMax,             SIGNAL(valueChanged(double)), SLOT(updateScaleY()));
    connect(ui->yStep,            SIGNAL(valueChanged(double)), SLOT(updateScaleY()));
    connect(ui->yTitle,           SIGNAL(textChanged(QString)), SLOT(setTitleY()));
    connect(ui->resolution,       SIGNAL(valueChanged(int)),    SLOT(setResolution(int)));
}

void PlotSettings::blockUpdating(bool block)
{
    ui->plotTitle->blockSignals(block);
    ui->opacity->blockSignals(block);
    ui->columnsCount->blockSignals(block);
    ui->plotExportHeight->blockSignals(block);
    ui->plotExportWidth->blockSignals(block);
    ui->xMin->blockSignals(block);
    ui->xMax->blockSignals(block);
    ui->xStep->blockSignals(block);
    ui->xTitle->blockSignals(block);
    ui->yMin->blockSignals(block);
    ui->yMax->blockSignals(block);
    ui->yStep->blockSignals(block);
    ui->yTitle->blockSignals(block);
    ui->resolution->blockSignals(block);
}

void PlotSettings::setExportSize()
{
    plot->setExportSize(
        QSizeF(ui->plotExportWidth->value(), ui->plotExportHeight->value())
    );
}

#include <QPrinter>
#include <QPrintDialog>
#include <qwt_plot_renderer.h>
void PlotSettings::printCurrentPlot()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if(dialog.exec() == QDialog::Accepted){
        QwtPlotRenderer().renderTo(plot, printer);
    }
}

#include <Path.h>
void PlotSettings::savePlotToImage()
{
    plot->exportToPng();
}

#include "LegendItem.h"
void PlotSettings::turnLegend(bool on)
{
    plot->getLegend()->setVisible(on);
    plot->replot();
}

void PlotSettings::setLegendFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, plot->getLegend()->font(), this, tr("Set legend font"));
    if(ok){
        plot->getLegend()->setFont(font);
        plot->replot();
    }
}

void PlotSettings::setLegendOpacity(int opacity)
{
    plot->getLegend()->setBackgroundOpacity(opacity);
    plot->replot();
}

void PlotSettings::setLegendMaxColumns(int count)
{
    plot->getLegend()->setMaxColumns(count);
    plot->replot();
}

void PlotSettings::setLegendPos()
{
    plot->getLegend()->setAlignment(
        Qt::AlignmentFlag(ui->horPos->itemData(ui->horPos->currentIndex()).toInt()) |
        Qt::AlignmentFlag(ui->verPos->itemData(ui->verPos->currentIndex()).toInt())
    );
    plot->replot();
}

void PlotSettings::createLookAndFeel()
{    
    ui->horPos->addItem(tr("Left"),   Qt::AlignLeft);
    ui->horPos->addItem(tr("Center"), Qt::AlignHCenter);
    ui->horPos->addItem(tr("Right"),  Qt::AlignRight);
    ui->verPos->addItem(tr("Top"),    Qt::AlignTop);
    ui->verPos->addItem(tr("Center"), Qt::AlignVCenter);
    ui->verPos->addItem(tr("Bottom"), Qt::AlignBottom);
}

void PlotSettings::retranslate()
{
    ui->retranslateUi(this);
    ui->horPos->setItemText(0, tr("Left"));
    ui->horPos->setItemText(1, tr("Center"));
    ui->horPos->setItemText(2, tr("Right"));
    ui->verPos->setItemText(0, tr("Top"));
    ui->verPos->setItemText(1, tr("Center"));
    ui->verPos->setItemText(2, tr("Bottom"));
}

#include <QMdiSubWindow>
#include "Plot.h"
void PlotSettings::catchPlot(QMdiSubWindow* window)
{
    if(window){
        plot = static_cast<Plot*>(window->widget());
        fillFromPlot();
        setEnabled(true);
        connect(plot, SIGNAL(zoomed()), SLOT(updateScale()));
    }
}

void PlotSettings::toDefaultState()
{
    setEnabled(false);
    plot = nullptr;
}

void PlotSettings::fillFromPlot()
{
    blockUpdating(true);
        fillTitle();
        fillLegend();
        fillExport();
        fillAxis(QwtPlot::xBottom, ui->xMin, ui->xMax, ui->xStep, ui->xTitle);
        fillAxis(QwtPlot::yLeft, ui->yMin, ui->yMax, ui->yStep, ui->yTitle);
    blockUpdating(false);
}

void PlotSettings::fillTitle()
{
    ui->plotTitle->setText(plot->title().text());
}

#include "LegendItem.h"
void PlotSettings::fillLegend()
{
    LegendItem* legend = plot->getLegend();
    {
        ui->settingsGroup->setChecked(legend->isVisible());
        ui->opacity->setValue(legend->backgroundBrush().color().alpha());
        ui->columnsCount->setValue(legend->maxColumns());
    }
    {
        const Qt::Alignment flags = plot->getLegend()->alignment();
        ui->horPos->setCurrentIndex(flags.testFlag(Qt::AlignLeft) ? 0 : flags.testFlag(Qt::AlignHCenter) ? 1 : 2);
        ui->verPos->setCurrentIndex(flags.testFlag(Qt::AlignTop)  ? 0 : flags.testFlag(Qt::AlignVCenter) ? 1 : 2);
    }
}

void PlotSettings::fillExport()
{
    QSizeF exportSize = plot->getExportSize();
    ui->plotExportWidth->setValue(exportSize.width());
    ui->plotExportHeight->setValue(exportSize.height());
    ui->resolution->setValue(plot->getResolution());
}

void PlotSettings::fillAxis(int axis, QDoubleSpinBox* min, QDoubleSpinBox* max, QDoubleSpinBox* step, QLineEdit* title)
{
    title->setText(plot->axisTitle(axis).text());
    fillAxisScale(axis, min, max, step);
}

void PlotSettings::fillAxisScale(int axis, QDoubleSpinBox* min, QDoubleSpinBox* max, QDoubleSpinBox* step)
{
    QwtInterval axisInterval = plot->axisInterval(axis);
    step->setValue(plot->axisStep(QwtPlot::Axis(axis)));
    min->setValue(axisInterval.minValue());
    max->setValue(axisInterval.maxValue());
}

void PlotSettings::updateScaleX()
{
    updateScaleAxis(QwtPlot::xBottom, ui->xMin, ui->xMax, ui->xStep);
}

void PlotSettings::updateScale()
{
    fillAxisScale(QwtPlot::xBottom, ui->xMin, ui->xMax, ui->xStep);
    fillAxisScale(QwtPlot::yLeft, ui->yMin, ui->yMax, ui->yStep);
}

void PlotSettings::setTitleX()
{
    setTitleAxis(QwtPlot::xBottom, ui->xTitle);
}

void PlotSettings::setTitleColorX()
{
    fillAxisTitle(QwtPlot::xBottom, fillWithColor);
}

void PlotSettings::setTitleFontX()
{
    fillAxisTitle(QwtPlot::xBottom, fillWithFont);
}

void PlotSettings::updateScaleY()
{
    updateScaleAxis(QwtPlot::yLeft, ui->yMin, ui->yMax, ui->yStep);
}

void PlotSettings::setTitleY()
{
    setTitleAxis(QwtPlot::yLeft, ui->yTitle);
}

void PlotSettings::setTitleColorY()
{
    fillAxisTitle(QwtPlot::yLeft, fillWithColor);
}

void PlotSettings::setTitleFontY()
{
    fillAxisTitle(QwtPlot::yLeft, fillWithFont);
}

void PlotSettings::updateScaleAxis(int axis, QDoubleSpinBox* min, QDoubleSpinBox* max, QDoubleSpinBox* step)
{
    plot->setAxisScale(axis, min->value(), max->value(), step->value());
    plot->replot();
}

void PlotSettings::setTitleAxis(int axis, QLineEdit* axisTitle)
{
    QwtText titleAxis = plot->axisTitle(axis);
    titleAxis.setText(axisTitle->text());
    plot->setAxisTitle(axis, titleAxis);
}

void PlotSettings::fillAxisTitle(int axis, const std::function<void (QWidget*, QwtText&)>& filler)
{
    QwtText titleAxis = plot->axisTitle(axis);
    filler(this, titleAxis);
    plot->setAxisTitle(axis, titleAxis);
}

void PlotSettings::setResolution(int resolution)
{
    plot->setResolution(resolution);
}
