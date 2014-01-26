#include <QApplication>
#include <Samples.h>
#include <CurvesFiller.h>
#include <Plot.h>
#include <Curves.h>
#include <QDebug>
#include <QFile>
#include <QTextStream>

void createTestData()
{
    QFile file("test.txt");
    if(file.open(QFile::WriteOnly)){
        QTextStream outer(&file);
        outer << "X Y Z \n";
        for(int i = 0; i < 10; ++i){
            for(int j = 0; j < 3; ++j){
                outer << j*i;
            }
            outer << "\n";
        }
        file.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createTestData();
    Samples* samples = new Samples();
    samples->load("test.txt");
    Plot* plot = new Plot();
    plot->show();
    Curves* curves = new Curves(plot, samples);
    CurvesFiller* curvesFiller = new CurvesFiller();
    curvesFiller->setCurves(curves);
    curvesFiller->show();
    return a.exec();
}
