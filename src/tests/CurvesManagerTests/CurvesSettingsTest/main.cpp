#include <QApplication>
#include <CurvesSettings.h>
#include <Curves.h>
#include <Plot.h>
#include <Samples.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
void createTestFile()
{
    QFile file("test.txt");
    if(file.open(QFile::WriteOnly)){
        QTextStream outer(&file);
        outer << "x y z\n0 0 0\n10 20 30";
        file.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        createTestFile();
        CurvesSettings* curvesSettings = new CurvesSettings();
        curvesSettings->show();
        Plot* plot = new Plot();
        Samples* samples = new Samples();
        samples->load("test.txt");
        samples->waitLoading();
        Curves* curves = new Curves(plot, samples);
        curves->setY(0);
        curves->setY(2);
        curves->setY(1);
        curvesSettings->setCurves(curves);
    return a.exec();
}
