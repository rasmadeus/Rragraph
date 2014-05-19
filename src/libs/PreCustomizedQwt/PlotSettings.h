#ifndef PLOTSETTINGS_H
#define PLOTSETTINGS_H

class QMdiSubWindow;
class Plot;
class QDoubleSpinBox;
class QLineEdit;
class QwtText;
#include <QWidget>

namespace Ui {
class PlotSettings;
}

class PlotSettingsFiller
{
    Q_DISABLE_COPY(PlotSettingsFiller)
protected:
    PlotSettingsFiller(Plot* donor);
    Plot* donor;
public:
    virtual ~PlotSettingsFiller();
    enum SettingsType
    {
        PLOT_TITLE_SETTINGS,
        ABSCISS_SETTINGS,
        ORDINATE_SETTINGS,
        EXPORT_SETTINGS,
        LEGEND_SETTINGS
    };
    static PlotSettingsFiller* make(SettingsType type, Plot* donor);
    virtual void fill(Plot* plot) = 0;
};

/*!
 * \brief The PlotSettings class - уважаемый разработчик, если ты решился
 *сделать из этого монолитного класса какой-нибудь мудрый паттерн вида
 *компановщик, прежде чем приступить к задуманному, подумай три раза
 *насколько это необходимо.
 */
class PlotSettings : public QWidget
{
    Q_OBJECT
public:
    explicit PlotSettings(QWidget *parent = 0);
    ~PlotSettings();
    void retranslate();
public slots:
    void catchPlot(QMdiSubWindow* window);
    void toDefaultState();
signals:
    void copySettings(PlotSettingsFiller*);
private slots:
    void setTitle(const QString& title);
    void setTitleColor();
    void setTitleFont();
    void turnLegend(bool on);
    void setLegendFont();
    void setLegendOpacity(int opacity);
    void setLegendMaxColumns(int count);
    void setLegendPos();
    void setExportSize();
    void setResolution(int resolution);
    void printCurrentPlot();
    void savePlotToImage();
    void updateScaleX();
    void setTitleX();
    void setTitleColorX();
    void setTitleFontX();
    void updateScaleY();
    void setTitleY();
    void setTitleColorY();
    void setTitleFontY();
    void copyPlotTitle();
    void copyX();
    void copyY();
    void copyExport();
    void copyLegend();
    void updateScale();
private:
    void createLookAndFeel();
    void routeActions();
    void updateScaleAxis(int axis, QDoubleSpinBox* min, QDoubleSpinBox* max, QDoubleSpinBox* step);
    void setTitleAxis(int axis, QLineEdit* axisTitle);
    void fillFromPlot();
    void fillTitle();
    void fillLegend();
    void fillPlotTitle(const std::function<void (QWidget*, QwtText&)>& filler);
    void fillAxisTitle(int axis, const std::function<void (QWidget*, QwtText&)>& filler);
    void fillAxisScale(int axis, QDoubleSpinBox* min, QDoubleSpinBox* max, QDoubleSpinBox* step);
    void fillExport();
    void blockUpdating(bool block);
    void fillAxis(
        int axis,
        QDoubleSpinBox* min,
        QDoubleSpinBox* max,
        QDoubleSpinBox* step,
        QLineEdit* title
    );
    Ui::PlotSettings *ui;
    Plot* plot;
};

#endif // PLOTSETTINGS_H
