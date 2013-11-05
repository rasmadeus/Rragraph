#ifndef EXPORTER_H
#define EXPORTER_H

class Plot;
#include "RestorablePath.h"
#include <qwt_plot_renderer.h>

class Exporter : public QwtPlotRenderer
{
public:
    Exporter();
    void exportOne(Plot* src);
    void exportOne(Plot* src, const QString& path);
    void printOne(Plot* src);
    void setExportPath(const QString& path);
    QString getExportPath();
private:
    RestorablePath exportPath;
};

#endif // EXPORTER_H
