#include "FontColorSettingsAble.h"

FontColorSettingsAble::FontColorSettingsAble(QWidget* parent) :
    PlotSettings(parent)
{
}

#include <QColorDialog>
#include <qwt_text.h>
void FontColorSettingsAble::setColor()
{
    emit catchPlot();
    QwtText text = getText();
    QColor color = QColorDialog::getColor(text.color(), this, tr("Set plot title color"));
    if(color.isValid()){
        text.setColor(color);
        setText(text);
    }
    emit freePlot();
}

#include <QFontDialog>
void FontColorSettingsAble::setFont()
{
    emit catchPlot();
    QwtText text = getText();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, text.font(), this, tr("Set plot title font"));
    if(ok){
        text.setFont(font);
        setText(text);
    }
    emit freePlot();
}
