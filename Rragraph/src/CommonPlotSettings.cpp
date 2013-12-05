#include "CommonPlotSettings.h"
#include "ui_CommonPlotSettings.h"

CommonPlotSettings::CommonPlotSettings(QWidget *parent) :
    PlotSettings(parent),
    ui(new Ui::CommonPlotSettings)
{
    ui->setupUi(this);
    connect(ui->title,      SIGNAL(textChanged(QString)), SLOT(setTitle(QString)));
    connect(ui->titleFont,  SIGNAL(clicked()),            SLOT(setTitleFont()));
    connect(ui->titleColor, SIGNAL(clicked()),            SLOT(setTitleColor()));
}

CommonPlotSettings::~CommonPlotSettings()
{
    delete ui;
}

void CommonPlotSettings::localeWasChanged(){
    ui->retranslateUi(this);
}

#include "Plot.h"
void CommonPlotSettings::dublicateValues(Plot* plot){
    plot->setTitle(owner->title());
}

void CommonPlotSettings::setNativeValues(){
    ui->title->setText(owner->title().text());
}

void CommonPlotSettings::setTitle(const QString& title)
{
    QwtText text = owner->title();
    text.setText(title);
    owner->setTitle(text);
}

#include <QColorDialog>
void CommonPlotSettings::setTitleColor()
{
    QwtText text = owner->title();
    QColor color = QColorDialog::getColor(text.color(), this, tr("Set title's color"));
    if(color.isValid()){
        text.setColor(color);
        owner->setTitle(text);
    }
}

#include <QFontDialog>
void CommonPlotSettings::setTitleFont()
{
    bool ok;
    QwtText text = owner->title();
    QFont font = QFontDialog::getFont(&ok, text.font(), this, tr("Set title's font"));
    if(ok){
        text.setFont(font);
        owner->setTitle(text);
    }
}
