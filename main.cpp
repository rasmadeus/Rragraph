#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include "MainWindow/MainWindow.h"

int main(int argc, char** argv)
{
    QApplication Rragraph(argc, argv);

        QApplication::setOrganizationName("Fakel");
        QApplication::setApplicationName("Rragraph");
        QApplication::setApplicationVersion("3.0");

        QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp1251"));

        QSplashScreen splash(QPixmap(":/resources/splash.png"));
        splash.show();

        MainWindow mainWindow;
        mainWindow.show();

        QStringList arguments = QApplication::arguments();
        if(arguments.size() > 1){
            QStringList files;
            for(int i=1; i<arguments.size(); ++i){
                files << arguments[i].replace("\\", "/");
            }
            mainWindow.loadFiles(files);
        }

        splash.finish(&mainWindow);

    return Rragraph.exec();
}
