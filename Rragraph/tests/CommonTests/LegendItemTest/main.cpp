#include <QApplication>
#include "../../../src/Plot.h"
#include "../../../src/LegendItem.h"
#include <qwt_plot_curve.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        Plot plot;
        plot.show();
        LegendItem legendItem();
       // legendItem.attach(&plot);

        QVector<QwtPlotCurve*> curves;
        for(int i=0; i< 10; ++i){
            QwtPlotCurve* curve = new QwtPlotCurve(QString("Curve №%1").arg(i));
            curves << curve;
            curve->attach(&plot);
        }

     return a.exec();
}
