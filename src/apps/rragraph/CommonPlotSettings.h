#ifndef COMMONPLOTSETTINGS_H
#define COMMONPLOTSETTINGS_H

#include "FontColorSettingsAble.h"

namespace Ui {
class CommonPlotSettings;
}

class CommonPlotSettings : public FontColorSettingsAble
{
    Q_OBJECT
public:
    explicit CommonPlotSettings(QWidget *parent = 0);
    ~CommonPlotSettings();
    void copySettingsTo(Plot* plot);
    void retranslate();
protected:
    void fillFromPlot();
    QwtText getText() const;
    void setText(const QwtText& text);
private slots:
    void setPlotTitle(const QString& title);
private:
    Ui::CommonPlotSettings *ui;
};

#endif // COMMONPLOTSETTINGS_H
