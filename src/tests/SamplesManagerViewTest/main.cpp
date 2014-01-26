#include <QApplication>
#include <SamplesManagerView.h>
#include <SamplesManager.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        SamplesManagerView* samplesManagerView = new SamplesManagerView();
        samplesManagerView->show();
        SamplesManager* samplesManager = new SamplesManager();
        samplesManagerView->setSamplesManager(samplesManager);
    return a.exec();
}
