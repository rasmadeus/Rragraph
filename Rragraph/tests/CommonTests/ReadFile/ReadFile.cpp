#include <QString>
#include <QtTest>
#include "../../../src/Loader.h"
#include "../../../src/Samples.h"
#include <QFile>
#include <QTextStream>
class ReadFile : public QObject
{
    Q_OBJECT

public:
    ReadFile();

private Q_SLOTS:
    void testCase1();
    void testCase2();
private:
    Loader* loader;
    Samples* samples;
};

ReadFile::ReadFile()
{
    samples = new Samples("");
    loader = new Loader(samples, this);
}

void ReadFile::testCase1()
{
    QString fileName("test.txt");
    QFile testFile(fileName);
    if(!testFile.open(QIODevice::WriteOnly)){
        QVERIFY(false);
        return;
    }
    QTextStream out(&testFile);
    out << "Head1 Head2 Head3 \n";
    out << "1      2     3    \n";
    out << "1.001 -2.003 5    \n\n";
    testFile.close();


    samples->setPath(fileName);

    loader->start();

    while(loader->isRunning()){
    }

    testFile.remove();

    QStringList headers = samples->getHeaders();
    QVERIFY(headers.size() == 3);

    QVector<qreal> column0 = samples->getSamples()[0];
    QVector<qreal> column1 = samples->getSamples()[1];
    QVector<qreal> column2 = samples->getSamples()[2];

    QCOMPARE(column0, QVector<qreal>() << 1 << 1.001);
    QCOMPARE(column1, QVector<qreal>() << 2 << -2.003);
    QCOMPARE(column2, QVector<qreal>() << 3 << 5);
}

void ReadFile::testCase2()
{
    QString fileName("test.txt");
    QFile testFile(fileName);
    if(!testFile.open(QIODevice::WriteOnly)){
        QVERIFY(false);
        return;
    }
    QTextStream out(&testFile);
    out << " \"Head1\" Head2 \" H e a d 3 \"  \n";
    out << "1      2     3    5\n";
    out << "1.001 -2.003     \n\n";
    testFile.close();

    loader->start();
    while(loader->isRunning()){
    }
    testFile.remove();

    QStringList headers = samples->getHeaders();
    QVERIFY(headers.size() == 3);
    QCOMPARE(headers[2], QString(" H e a d 3 "));

    QVector<qreal> column0 = samples->getSamples()[0];
    QVector<qreal> column1 = samples->getSamples()[1];
    QVector<qreal> column2 = samples->getSamples()[2];

    QCOMPARE(column0, QVector<qreal>() << 1 << 1.001);
    QCOMPARE(column1, QVector<qreal>() << 2 << -2.003);
    QCOMPARE(column2, QVector<qreal>() << 3 << 0);
}

QTEST_APPLESS_MAIN(ReadFile)

#include "ReadFile.moc"
