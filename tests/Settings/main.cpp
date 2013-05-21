#include <QApplication>
#include "../../Styles/View/StylesEditor.h"

int main(int argc, char** argv){
    QApplication Settings_test(argc, argv);
    QApplication::setOrganizationName("The Fakel Engineering Design Bureau");
    QApplication::setApplicationName("Rragraph");
    QApplication::setApplicationVersion("3.0");
    StylesEditor editor;
    editor.show();
    return Settings_test.exec();
}
