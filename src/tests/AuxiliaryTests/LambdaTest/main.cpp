#include <QCoreApplication>
#include <QVector>
#include <iostream>
#include <QDebug>
#include <functional>

QVector<double> values(10);

void worker(const std::function<void(double& value)>& doer)
{
    std::for_each(values.begin(), values.end(), doer);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
        std::generate(values.begin(), values.end(), std::rand);
        std::for_each(values.begin(), values.end(), [](double x){qDebug() << x;});
        qDebug() << "*******";
        worker([&](double& x){x = x * x;});
        worker([](double x){qDebug() << x;});
    return a.exec();
}
