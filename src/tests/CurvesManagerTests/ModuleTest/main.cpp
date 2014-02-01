#include <QApplication>
#include <CurvesManagerView.h>
#include <SamplesManager.h>
#include <Plot.h>
#include <CurvesManager.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        SamplesManager* samplesManager = new SamplesManager();
        CurvesManagerView* curvesManagerView = new CurvesManagerView(samplesManager);
        curvesManagerView->setWindowTitle("Curves manager view");
        curvesManagerView->show();
        Plot* plot = new Plot();
        plot->show();
        CurvesManager* curvesManager = new CurvesManager(samplesManager, plot);        
        curvesManagerView->setCurvesManager(curvesManager);
    return a.exec();
}
