#include "Project.h"

#include <Path.h>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include "Groups.h"
#include <QApplication>
class Project::ProjectPrivateData
{
public:
    ProjectPrivateData(Groups* groups):
        currentProjectPath("paths/lastProjectPath"),
        groups(groups)
    {
    }

    void close()
    {
        pro = QJsonDocument();
        groups->closeGroups();
    }

    void load(const QString& pathToPro)
    {
        QFile proFile(pathToPro);
        if(proFile.open(QFile::ReadOnly | QFile::Text)){
            close();
            pro = QJsonDocument::fromJson(proFile.readAll());
            groups->restore(pro.object(), currentProjectPath);
        }
    }    

    void save(const QString& pathToPro)
    {
        QFile proFile(pathToPro);
        if(proFile.open(QFile::WriteOnly | QFile::Text)){
            QTextStream proFileWriter(&proFile);
            proFileWriter.setCodec("UTF-8");
                fillPro();
            proFileWriter << pro.toJson(QJsonDocument::Indented);
        }
    }

    void fillPro()
    {
        QJsonObject root;
            root.insert("rragraphVersion", QJsonValue::fromVariant("4.2.0"));
            groups->serialize(root, currentProjectPath);
        pro.setObject(root);
    }

    QString rragraphProFilter() const
    {
        return tr("Rragraph pro file") + "(*.rgf);;" + Path::getTemplate(Path::ALL_FILES);
    }

    Path currentProjectPath;
    QJsonDocument pro;
    Groups* groups;
};

#include <QWidget>
Project::Project(Groups* groups, QWidget* parent) :
    QObject(parent),
    parent(parent)
{
    d = new ProjectPrivateData(groups);
}

Project::~Project()
{
    delete d;
}

void Project::load()
{
    const bool ok = d->currentProjectPath.setOpenFileName(
        parent,
        tr("Load project"),
        d->rragraphProFilter()
    );
    if(ok){
        load(d->currentProjectPath.getPath());
    }
}

void Project::load(const QString& path)
{
    emit beginReading();
        emit wasClosed();
        d->currentProjectPath.setPath(path);
        d->load(path);
        emit wasReplaced(path);
    emit endReading();
}

#include <QAction>
void Project::load(QAction* action)
{
    d->currentProjectPath.setPath(action->data().toString());
    reload();
}

void Project::reload()
{
    emit wasClosed();
    if(d->currentProjectPath.isEmpty()){
        load();
    }
    else{
        load(d->currentProjectPath.getPath());        
    }
}

void Project::close()
{
    d->groups->toDefaultState();
    d->currentProjectPath.clear();
    emit wasClosed();
}

bool Project::save()
{
    if(d->currentProjectPath.isEmpty()){
        return saveAs();
    }
    else{
        d->save(d->currentProjectPath.getPath());
        return true;
    }
}

bool Project::saveAs()
{
    const bool ok = d->currentProjectPath.setSaveFileName(
        parent,
        tr("Save project as"),
        d->rragraphProFilter()
    );
    if(ok){
        d->save(d->currentProjectPath.getPath());
        emit wasReplaced(d->currentProjectPath.getPath());
    }
    return ok;
}

#include <QFileDialog>
#include <QMessageBox>
void Project::forKojnevAlexandrNikolayevich()
{
    const QString destDir = QFileDialog::getExistingDirectory(parent, tr("Copy there"), d->currentProjectPath.getPath());
    if(!destDir.isEmpty()){
        const QString newPath = destDir + "/" + d->currentProjectPath.getPathInfo().fileName();
        if (newPath != d->currentProjectPath.getPath()){
            QFile::remove(newPath);
        }
        if(QFile::copy(d->currentProjectPath.getPath(), newPath)){
            load(newPath);
        }
        else{
            QMessageBox::warning(parent, tr("Copy error"), tr("I can't copy pro file to that folder!"));
        }
    }
}

#include <VersionConverter.h>
void Project::forDeminValeriyNikolayevich()
{
    const bool ok = d->currentProjectPath.setOpenFileName(
        parent,
        tr("Load project"),
        d->rragraphProFilter()
    );
    if(ok){
        emit beginReading();
            emit wasClosed();
                d->pro = jumpFromThirdToFourth(d->currentProjectPath.getPath());
                d->groups->closeGroups();
                d->groups->restore(d->pro.object(), d->currentProjectPath);
            emit wasReplaced(d->currentProjectPath.getPath());
        emit endReading();
    }
}

const QString& Project::getPathToPro() const
{
    return d->currentProjectPath.getLastPath();
}
