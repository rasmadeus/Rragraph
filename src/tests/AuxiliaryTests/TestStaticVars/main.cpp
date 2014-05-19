#include <QCoreApplication>

static int i = 0;
class Test
{
public:
    Test(int* i):
        i(i)
    {
    }

    int* i;
};

#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Test test(&i);
    qDebug() << i << *(test.i);
    i = 5;
    qDebug() << i << *(test.i);
    return a.exec();
}
