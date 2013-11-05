#include "LegendSettings.h"
#include "ui_LegendSettings.h"

LegendSettings::LegendSettings(QWidget *parent) :
    PlotSettings(parent),
    ui(new Ui::LegendSettings)
{
    ui->setupUi(this);

    ui->horizontalAlign->addItem(tr("Left"),   Qt::AlignLeft);
    ui->horizontalAlign->addItem(tr("Center"), Qt::AlignHCenter);
    ui->horizontalAlign->addItem(tr("Right"),  Qt::AlignRight);

    ui->verticalAlign->addItem(tr("Top"),    Qt::AlignTop);
    ui->verticalAlign->addItem(tr("Center"), Qt::AlignVCenter);
    ui->verticalAlign->addItem(tr("Bottom"), Qt::AlignBottom);

    connect(ui->font,            SIGNAL(clicked()),                SLOT(setFont()));
    connect(ui->verticalAlign,   SIGNAL(currentIndexChanged(int)), SLOT(alignmentChanged()));
    connect(ui->horizontalAlign, SIGNAL(currentIndexChanged(int)), SLOT(alignmentChanged()));
    connect(ui->opacity,         SIGNAL(valueChanged(int)),        SLOT(setOpacity(int)));
    connect(ui->legend,          SIGNAL(toggled(bool)),            SLOT(turnLegend(bool)));
    connect(ui->dublicate,       SIGNAL(clicked()),                SLOT(dublicateValues()));
    connect(ui->columns,         SIGNAL(valueChanged(int)),        SLOT(setMaximumColumns(int)));
}

void LegendSettings::alignmentChanged(){
    setAlignment(owner);
}

void LegendSettings::setOpacity(int opacity){
    setOpacity(owner, opacity);
}

void LegendSettings::localeWasChanged(){
    ui->retranslateUi(this);
    ui->horizontalAlign->setItemText(0, tr("Left"));
    ui->horizontalAlign->setItemText(1, tr("Center"));
    ui->horizontalAlign->setItemText(2, tr("Right"));
    ui->verticalAlign->setItemText(0, tr("Top"));
    ui->verticalAlign->setItemText(1, tr("Center"));
    ui->verticalAlign->setItemText(2, tr("Bottom"));
}

LegendSettings::~LegendSettings(){
    delete ui;
}

#include "Plot.h"
#include "LegendItem.h"
void LegendSettings::setMaximumColumns(int count)
{
    owner->getLegend()->setMaxColumns(count);
    owner->replot();
}

void LegendSettings::setNativeValues()
{
    ui->legend->setChecked(owner->getLegend()->isVisible());
    ui->opacity->setValue(owner->getLegend()->backgroundBrush().color().alpha());
    ui->columns->setValue(owner->getLegend()->maxColumns());

    const Qt::Alignment flags = owner->getLegend()->alignment();
    ui->horizontalAlign->setCurrentIndex(
        flags.testFlag(Qt::AlignLeft) ? 0 : flags.testFlag(Qt::AlignHCenter) ? 1 : 2
    );
    ui->verticalAlign->setCurrentIndex(
        flags.testFlag(Qt::AlignTop)  ? 0 : flags.testFlag(Qt::AlignVCenter) ? 1 : 2
    );
}

void LegendSettings::turnLegend(bool on)
{
    if(!owner){
        ui->legend->setChecked(false);
        return;
    }
    owner->getLegend()->setVisible(on);
    owner->replot();
}

#include <QFontDialog>
void LegendSettings::setFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, owner->getLegend()->font(), this, tr("Set legend font"));
    if(ok){
        owner->getLegend()->setFont(font);
        owner->replot();
    }
}

void LegendSettings::setOpacity(Plot* plot, int opacity)
{
    plot->getLegend()->setBackgroundOpacity(opacity);
    plot->replot();
}

void LegendSettings::setAlignment(Plot* plot)
{
    plot->getLegend()->setAlignment(
        Qt::AlignmentFlag(ui->horizontalAlign->itemData(ui->horizontalAlign->currentIndex()).toInt())|
        Qt::AlignmentFlag(ui->verticalAlign->itemData(ui->verticalAlign->currentIndex()).toInt())
    );
    plot->replot();
}

void LegendSettings::dublicateValues(Plot* plot)
{
    setAlignment(plot);
    setOpacity(plot, owner->getLegend()->backgroundBrush().color().alpha());
    plot->getLegend()->setMaxColumns(ui->columns->value());
}
