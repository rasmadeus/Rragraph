#include <QApplication>

#include "MainWindow.h"
int main(int argc, char *argv[])
{
    QApplication Rragraph(argc, argv);
    QApplication::setOrganizationName("Fakel");
    QApplication::setApplicationName("Rragraph");
    QApplication::setApplicationVersion("4.0");
        MainWindow view;
        view.show();
    return Rragraph.exec();
}
