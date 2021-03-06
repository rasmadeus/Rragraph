#ifndef GROUP_H
#define GROUP_H

class Path;
class CurvesManagerView;
class SamplesManager;
class PlotWithCurves;
class PlotSettings;
class PlotSettingsFiller;
#include <QMdiArea>
#include <functional>

class Group : public QMdiArea
{
    Q_OBJECT
public:
    enum TileType
       {
           GRID_STRAIGHT,
           GRID_REVERSE,
           VERTICAL_STRAIGHT,
           VERTICAL_REVERSE
       };
    explicit Group(QWidget* parent = 0);
    ~Group();
    QList<QMdiSubWindow*> visibleWindows();
    void setTileType(TileType tileType);
    TileType getTileType() const;
    SamplesManager* getSamplesManager() const;
    bool isEmpty() const;
    const QString& getName() const;
    bool nameIsEmpty() const;
    void serialize(QJsonArray& groupsSettings, const Path& proPath) const;
    void restore(const QJsonObject& groupSettings, const Path& proPath);
    void retranslate();
    void copySettings(PlotSettingsFiller* filler);
    void setInitialLoadingPath(const QString& path);
signals:
    void noMorePlots();
public slots:
    void setName(const QString& name);
    PlotWithCurves* insertPlot();
    void tile();
    void autoscale();
    void exportToPng(const QString& dir);
    void exportToPdf(const QString& fileName);
private slots:
    void retitle();
private:
    void serializePlots(QJsonObject& groupSettings) const;
    void restorePlots(const QJsonObject& groupSettings);
    void forEachPlotDo(const std::function<void (QMdiSubWindow*, PlotWithCurves*)>& action) const;
    TileType tileType;
    QString name;
    SamplesManager* samplesManager;
    CurvesManagerView* curvesManagerView;
};

#endif // GROUP_H
