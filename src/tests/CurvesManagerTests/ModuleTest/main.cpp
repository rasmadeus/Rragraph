#include <QApplication>
#include <CurvesManagerView.h>
#include <SamplesManager.h>
#include <Plot.h>
#include <CurvesManager.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        CurvesManagerView* curvesManagerView = new CurvesManagerView();
        curvesManagerView->show();
        Plot* plot = new Plot();
        plot->show();
        SamplesManager* samplesManager = new SamplesManager();
        CurvesManager* curvesManager = new CurvesManager(samplesManager, plot);
        curvesManagerView->setCurvesManager(curvesManager);
    return a.exec();
}
