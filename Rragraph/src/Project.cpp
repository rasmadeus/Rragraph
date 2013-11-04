#include "Project.h"
#include <QDebug>
Project::Project(QObject *parent) :
    QObject(parent),
    lastPath("lastProjectPath")
{
}

#include <QFileDialog>
void Project::load()
{
    const QString path = QFileDialog::getOpenFileName(
        static_cast<QWidget*>(parent()),
        tr("Open a project"),
        lastPath(),
        tr("Rragraph file(*.rgf);;All files(*)")
    );
    if(!path.isEmpty()){
        lastPath = path;
        reload();
    }
}

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
void Project::reload()
{
    QFile file(lastPath());
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        showLoadingError();
        return;
    }
    doc = QJsonDocument::fromJson(file.readAll());
    applyProject();
}

void Project::saveAs()
{
    const QString path = QFileDialog::getSaveFileName(
            static_cast<QWidget*>(parent()),
            tr("Save this project as"),
            lastPath(),
            tr("Rragraph file(*.rgf)")
        );
    if(!path.isEmpty()){
        lastPath = path;
        resave();
    }   
}

void Project::resave()
{
    QFile file(lastPath());
    if(!file.open(QFile::WriteOnly)){
        showSavingError();
        return;
    }
    QTextStream out(&file);
    fillProject();
    out << doc.toJson(QJsonDocument::Indented);
}
#include <QJsonObject>
#include "MdiArea.h"
#include <QJsonArray>
void Project::fillProject()
{
    QJsonObject obj;
    obj["windows"] = MdiArea::getInstance()->serialize();
    doc.setObject(obj);
}

void Project::applyProject()
{
    const QJsonObject obj = doc.object();
    MdiArea::getInstance()->restore(obj.value("windows").toObject());
}

#include <QMessageBox>
void Project::showLoadingError()
{
    QMessageBox::warning(
        static_cast<QWidget*>(parent()),
        tr("Project loading error"),
        tr("The project file is invalid!")
    );
}

void Project::showSavingError()
{
    QMessageBox::warning(
        static_cast<QWidget*>(parent()),
        tr("Project saving error"),
        tr("The file for saving is not available!")
    );
}
