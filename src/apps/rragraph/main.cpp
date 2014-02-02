#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication rragraph(argc, argv);
    QApplication::setOrganizationName("Fakel");
    QApplication::setApplicationName("Rragraph");
    QApplication::setApplicationVersion("4.1");
        MainWindow mainWindow;
        mainWindow.show();
    return rragraph.exec();
}
