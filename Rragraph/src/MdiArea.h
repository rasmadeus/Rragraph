#ifndef MDIAREA_H
#define MDIAREA_H

class Plot;
#include "global.h"
#include <QMdiArea>

class MdiArea : public QMdiArea
{
    Q_OBJECT
    SINGLETON_HEADER(MdiArea, QWidget)
public slots:
    Plot* insertPlot();
    void exportToPng();
    void print();
    void autoscale();
    void tile();
    void changeTileType(QAction* action);
    QList<QMdiSubWindow*> visibleWindows();
signals:
    void noMoreWindow(Plot* null);
public:
    enum TileType
    {
        GRID_HORIZONTAL,
        VERTICAL_STRAIGHT,
        VERTICAL_REVERSE
    };
    void localeWasChanged();
    void serialize(QJsonObject& root) const;
    void restore(const QJsonObject& root);
    void serializeCurves(QJsonObject& root) const;
    void restoreCurves(int iFile, const QJsonObject &root);
private slots:
    void retitle();
    void destroyedWindow();
private:
    TileType tileType;
};

#endif // MDIAREA_H
