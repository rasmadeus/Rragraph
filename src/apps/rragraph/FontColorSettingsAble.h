#ifndef FONTCOLORSETTINGSABLE_H
#define FONTCOLORSETTINGSABLE_H

#include "PlotSettings.h"
class QwtText;

class FontColorSettingsAble : public PlotSettings
{
    Q_OBJECT
public:
    explicit FontColorSettingsAble(QWidget *parent = 0);
protected slots:
    void setColor();
    void setFont();
protected:
    virtual QwtText getText() const = 0;
    virtual void setText(const QwtText& text) = 0;
};

#endif // FONTCOLORSETTINGSABLE_H
