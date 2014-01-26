#include <QCoreApplication>
#include <RragraphProCreator.h>
#include <GroupProCreator.h>
#include <CurveProCreator.h>
#include <CurvesProCreator.h>
#include <PlotProCreator.h>
#include <QFile>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    RragraphProCreator pro;
        GroupProCreator group;
        group.setTitle("FirstGroup");
        group.appendFile("../test.txt");
        group.appendFile("test/test.txt");
            CurvesProCreator curves;
            curves.setFile(0);
            curves.setPlot(1);
            curves.setX(1);
                CurveProCreator curve;
                curve.setAddendX(1);
                curve.setAddendY(2);
                curve.setColor("#ff00ff");
                curve.setDashPattern("1 2 3");
                curve.setMultY(2);
                curve.setStep(10);
                curve.setSymbolStyle(-1);
                curve.setWidth(2);
                curve.setY(2);
            curves.append(curve);
                curve.clear();
                curve.setWidth(3);
                curve.setColor("#fa42a1");
                curve.setY(1);
            curves.append(curve);
        group.appendCurve(curves);
            PlotProCreator plot;
            plot.setTitle("Plot1");
            plot.setLegendPosition(1, 2);
            plot.setLegendOpacity(0.6);
        group.appendPlot(plot);
            plot.setTitle("Plot2");
            plot.setLegendOpacity(1);
        group.appendPlot(plot);
    pro.appendGroup(group);
    pro.save("RragraphProCreatorTest.txt");
    return a.exec();
}
