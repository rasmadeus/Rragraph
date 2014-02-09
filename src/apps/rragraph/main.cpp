#include "MainWindow.h"
#include <QApplication>
#include <QFont>
int main(int argc, char *argv[])
{
    QApplication rragraph(argc, argv);
    QApplication::setOrganizationName("Fakel");
    QApplication::setApplicationName("Rragraph");
    QApplication::setApplicationVersion("4.1");
    QApplication::setFont(QFont(":/res/mainWindow/bicubic.OTF", 10));
        MainWindow mainWindow;
        mainWindow.show();
    return rragraph.exec();
}
