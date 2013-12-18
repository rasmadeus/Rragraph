#include "SamplesViewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        SamplesViewer samplesViewer;
        samplesViewer.show();
    return a.exec();
}
