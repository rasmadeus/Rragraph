#ifndef GROUP_H
#define GROUP_H

class CurvesManagerView;
class SamplesManager;
class PlotWithCurves;
class PlotSettings;
#include <QMdiArea>
#include <functional>

class Group : public QMdiArea
{
    Q_OBJECT
public:
    enum TileType
       {
           GRID_HORIZONTAL,
           VERTICAL_STRAIGHT,
           VERTICAL_REVERSE
       };
    explicit Group(QWidget* parent = 0);
    ~Group();
    QList<QMdiSubWindow*> visibleWindows();
    void setTileType(TileType tileType);
    TileType getTileType() const;
    SamplesManager* getSamplesManager() const;
    void dublicateSettings(PlotSettings* plotSettings);
    bool isEmpty() const;
    const QString& getName() const;
    bool nameIsEmpty() const;
public slots:
    void setName(const QString& name);
    PlotWithCurves* insertPlot();
    void tile();
    void autoscale();
    void exportToPng(const QString& dir);
private slots:
    void retitle();
private:
    void forEachPlotDo(const std::function<void (QMdiSubWindow*, PlotWithCurves*)>& action);
    TileType tileType;
    QString name;
    SamplesManager* samplesManager;
    CurvesManagerView* curvesManagerView;
};

#endif // GROUP_H
