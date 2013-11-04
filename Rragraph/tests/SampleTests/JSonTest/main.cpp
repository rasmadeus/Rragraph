#include <QCoreApplication>
#include <QFont>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QColor>
#include <QJsonArray>
#include <QVariantMap>
#include <QVariantList>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVariantMap s1;
    s1["size"] = 10;
    s1["value"] = 35;

    QVariantMap s2;
    s2["font"] = "arial";
    s2["color"] = "red";
    s2["s1"] = s1;

    QJsonDocument doc = doc.fromVariant(s2);

    qDebug() << doc.toJson(QJsonDocument::Indented);
    return a.exec();
}
