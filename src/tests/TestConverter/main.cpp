#include <QCoreApplication>
#include <VersionConverter.h>
#include <iostream>
#include <QDebug>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
void save(const QJsonDocument& doc, const QString& pathToPro)
{
    QFile proFile(pathToPro);
    if(proFile.open(QFile::WriteOnly | QFile::Text)){
        QTextStream proFileWriter(&proFile);
        proFileWriter.setCodec("UTF-8");
        proFileWriter << doc.toJson(QJsonDocument::Indented);
    }
}

#include <QFileInfo>
int main(int argc, char *argv[])
{
    QCoreApplication testConverter(argc, argv);
    const QString prefix = testConverter.applicationDirPath() + "/../../../../src/tests/TestConverter/";
    QJsonDocument doc = jumpFromThirdToFourth(prefix + "rragraph_3_pro_file.rgf");
    save(doc, prefix + "rragraph_4_pro_file.rgf");
    qDebug() << "It have been done.";
    return testConverter.exec();
}
