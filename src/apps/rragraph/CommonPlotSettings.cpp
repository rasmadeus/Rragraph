#include "CommonPlotSettings.h"
#include "ui_CommonPlotSettings.h"

CommonPlotSettings::CommonPlotSettings(QWidget *parent) :
    FontColorSettingsAble(parent),
    ui(new Ui::CommonPlotSettings)
{
    ui->setupUi(this);
    connect(ui->plotTitle, SIGNAL(textChanged(QString)), SLOT(setPlotTitle(QString)));
    connect(ui->plotTitleColor, SIGNAL(clicked()), SLOT(setColor()));
    connect(ui->plotTitleFont, SIGNAL(clicked()), SLOT(setFont()));
    connect(ui->copy, SIGNAL(clicked()), SIGNAL(dublicateSettings()));
}

CommonPlotSettings::~CommonPlotSettings()
{
    delete ui;
}

#include <Plot.h>
void CommonPlotSettings::fillFromPlot()
{
    ui->plotTitle->setText(plot->title().text());
}

void CommonPlotSettings::setPlotTitle(const QString& title)
{
    plot->setTitle(title);
}

void CommonPlotSettings::copySettingsTo(Plot* plot)
{
    QwtText currentPlotTitle = this->plot->title();
    currentPlotTitle.setText(plot->title().text());
    plot->setTitle(currentPlotTitle);
}

QwtText CommonPlotSettings::getText() const
{
    return plot->title();
}

void CommonPlotSettings::setText(const QwtText& text)
{
    plot->setTitle(text);
}
