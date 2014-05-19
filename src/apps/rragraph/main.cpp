#include "MainWindow.h"
#include <QApplication>
#include <QFont>
#include <QFontDatabase>

void setAppFont()
{
    QApplication::setFont(QFont("Sans", 10));
}

QStringList args()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    return args;
}

int main(int argc, char *argv[])
{
    QApplication rragraph(argc, argv);
    QApplication::setOrganizationName("Fakel");
    QApplication::setApplicationName("Rragraph");
    QApplication::setApplicationVersion("4.2.0.");
        setAppFont();
        MainWindow mainWindow;
        mainWindow.show();
        mainWindow.processArgs(args());       
    return rragraph.exec();
}
