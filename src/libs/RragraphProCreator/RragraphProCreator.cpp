#include "RragraphProCreator.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
bool RragraphProCreator::read(const QString& pathToPro)
{
    QFile proFile(pathToPro);
    if(proFile.open(QFile::ReadOnly | QFile::Text)){
        QJsonDocument pro = QJsonDocument::fromJson(proFile.readAll());
        groups = pro.object().value("groups").toArray();
        return true;
    }
    return false;
}

#include <QTextStream>
bool RragraphProCreator::save(const QString& pathToPro) const
{
    QFile proFile(pathToPro);
    if(proFile.open(QFile::WriteOnly | QFile::Text)){
        QTextStream proFileWriter(&proFile);
        proFileWriter.setCodec("UTF-8");
        QJsonDocument pro;
        QJsonObject root;
        root.insert("rragraphVersion", QJsonValue::fromVariant("4.2.0"));
        root.insert("groups", groups);
        pro.setObject(root);
        proFileWriter << pro.toJson(QJsonDocument::Indented);
        return true;

    }
    return false;
}

void RragraphProCreator::clear()
{
    groups = QJsonArray();
}

void RragraphProCreator::createGroup(const QString& groupTitle)
{
    QJsonObject group;
    group.insert("title", groupTitle);
    groups.append(group);
}
