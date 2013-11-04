#include <QString>
#include <QStringList>
#include <QtTest>

class HeadersCreator : public QObject
{
    Q_OBJECT
public:
    HeadersCreator();

private Q_SLOTS:
    void testHeadersCreator();
    void testHeadersCreator_data();
    void testQuotes();
    void testQuotes_data();
};

HeadersCreator::HeadersCreator()
{
}

#include <QRegExp>
#include <QDebug>
QStringList getHeaders(const QString& src)
{
    QRegExp rx("(\"[^\"]+\"|\\S+)");
    QStringList result;
    int pos = 0;
    while((pos = rx.indexIn(src, pos)) != -1){
        result << rx.cap(1);
        pos += rx.matchedLength();
    }
    return result;
}

void HeadersCreator::testHeadersCreator()
{
    QFETCH(QString, src);
    QFETCH(QStringList, rightResult);
    QCOMPARE(rightResult, getHeaders(src));
}

void HeadersCreator::testHeadersCreator_data()
{
    QTest::addColumn<QString>("src");
    QTest::addColumn<QStringList>("rightResult");
    QTest::newRow("0") << QString("\" H e a d e r \"")           << (QStringList() << "\" H e a d e r \"");
    QTest::newRow("1") << QString("Header")                      << (QStringList() << "Header");
    QTest::newRow("2") << QString(" Header Header2 \"")          << (QStringList() << "Header"       << "Header2" <<"\"" );
    QTest::newRow("3") << QString("\"  \"")                      << (QStringList() << "\"  \"");
    QTest::newRow("4") << QString("\"\"\"")                      << (QStringList() << "\"\"\"");
    QTest::newRow("5") << QString("\" \" \"")                    << (QStringList() << "\" \""        << "\"");
    QTest::newRow("6") << QString("\" Hea der\" Header \"][,-+") << (QStringList() << "\" Hea der\"" << "Header"  << "\"][,-+");
    QTest::newRow("7") << QString("\" \"Header")                      << (QStringList() << "\" \"" << "Header");
}

void removeQuotes(QString& src)
{
    if(src.size() > 2){
        if(std::find(src.begin()+1, src.end()-1, '"') != (src.end())){
            src.replace("\"", "");
        }
    }
}

void HeadersCreator::testQuotes()
{
    QFETCH(QString, src);
    QFETCH(QString, result);
    removeQuotes(src);
    QCOMPARE(src, result);
}

void HeadersCreator::testQuotes_data()
{
    QTest::addColumn<QString>("src");
    QTest::addColumn<QString>("result");
    QTest::newRow("0") << QString("Header") << QString("Header");
    QTest::newRow("1") << QString("\"Header\"") << QString("Header");
    QTest::newRow("2") << QString("\" \"") << QString(" ");
    QTest::newRow("3") << QString("\"") << QString("\"");
    QTest::newRow("4") << QString("\"\"") << QString("\"\"");
}

QTEST_APPLESS_MAIN(HeadersCreator)

#include "HeadersCreator.moc"
