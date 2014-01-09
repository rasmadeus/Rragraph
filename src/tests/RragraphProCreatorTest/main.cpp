#include <QCoreApplication>
#include <RragraphProCreator.h>

#include <QFile>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    RragraphProCreator pro;
    pro.createGroup("FirstGroup");
    pro.createGroup("SecondGroup");
    pro.save("RragraphProCreatorTest.txt");
    return a.exec();
}
