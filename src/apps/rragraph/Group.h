#ifndef GROUP_H
#define GROUP_H

class CurvesCustomizer;
class SamplesManager;
class PlotWithCurves;
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
public slots:
    void setName(const QString& name);
    bool nameIsEmpty() const;
    PlotWithCurves* insertPlot();
    void tile();
    void autoscale();
private slots:
    void retitle();
private:
    void forEachPlotDo(const std::function<void (PlotWithCurves*)>& action);
    TileType tileType;
    QString name;
    SamplesManager* samplesManager;
    CurvesCustomizer* curvesCustomizer;
};

#endif // GROUP_H
