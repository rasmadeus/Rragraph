#include <QtCore/QString>
#include <QtTest/QtTest>

#include "../../Canvas/Data/FilePathParsing/FilePathParsing.h"

class FilePathParsingTest : public QObject
{
    Q_OBJECT

public:
    FilePathParsingTest();

private Q_SLOTS:
    void relative();
    void relative_data();
    void absolute();
    void absolute_data();
};

FilePathParsingTest::FilePathParsingTest()
{
}

void FilePathParsingTest::relative()
{
    QString project_path = "C:/Dir/Habrahabr/project.rgf";
    QFETCH(QString, path);
    QFETCH(QString, result);
    qDebug() << project_path << path << result;
    QCOMPARE(FilePathParsing::relative_path(project_path, path), result);
}

void FilePathParsingTest::relative_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("result");
    QTest::newRow("0") << "C:/Dir/Habrahabr/It's very nice/file.txt" << "It's very nice/file.txt";
    QTest::newRow("1") << "C:/file.txt"                              << "../../file.txt";
    QTest::newRow("2") << "C:/Dir/Other dir/file.txt"                << "../Other dir/file.txt";
    QTest::newRow("3") << "F:/file.txt"                              << "F:/file.txt";
}


void FilePathParsingTest::absolute()
{
    QString project_path = "C:/Dir/Dir/project.rgf";
    QFETCH(QString, path);
    QFETCH(QString, result);
    qDebug() << project_path << path << result;
    QCOMPARE(FilePathParsing::absolute_path(path, project_path), result);
}

void FilePathParsingTest::absolute_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("result");
    QTest::newRow("0") << "../../file.txt"           << "C:/file.txt";
    QTest::newRow("1") << "NewDir/SuperDir/file.txt" << "C:/Dir/Dir/NewDir/SuperDir/file.txt";
    QTest::newRow("2") << "../NewDir/file.txt"       << "C:/Dir/NewDir/file.txt";
    QTest::newRow("3") << "F:/Dir/1.txt"             << "F:/Dir/1.txt";
}

QTEST_APPLESS_MAIN(FilePathParsingTest);

#include "FilePathParsingTest.moc"
