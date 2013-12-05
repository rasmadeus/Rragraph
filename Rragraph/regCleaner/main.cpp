#include <QCoreApplication>

#include <QSettings>
#include <iostream>
void clearRegisterFromRragraph()
{
    QSettings().clear();
    std::cout << "The register have been cleaned from Rragraph's settings!" << std::endl;
    std::cout << "Good bye!" << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication RragraphRegCleaner(argc, argv);
    QCoreApplication::setOrganizationName("Fakel");
    QCoreApplication::setApplicationName("Rragraph");
    QCoreApplication::setApplicationVersion("4.0");
    char ch;
    while(true){
        std::cout << "Would you like to clean the register from Rragraph? y/n" << std::endl;
        std::cout << "Your answer: "; std::cin >> ch;
        switch(ch){
            case 'y': clearRegisterFromRragraph(); QCoreApplication::quit(); break;
        case 'n' : RragraphRegCleaner.quit(); QCoreApplication::quit(); break;
            default: std::cout << "I do not know what you said. Repeat, please." << std::endl; break;
        }

    }
    return RragraphRegCleaner.exec();
}
