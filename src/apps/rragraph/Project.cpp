#include "Project.h"

#include <Path.h>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include "Groups.h"
class Project::ProjectPrivateData
{
public:
    ProjectPrivateData(Groups* groups):
        currentProjectPath("appSettings.ini","paths/lastProjectPath"),
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

    Path currentProjectPath;
    QJsonDocument pro;
    Groups* groups;
};

#include <QWidget>
Project::Project(Groups* groups, QWidget* parent) :
    QObject(parent)
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
        static_cast<QWidget*>(this->parent()),
        tr("Load project"),
        tr("Rragraph pro file") + "(*.rgf);;" + tr("All files") + "(*)"
    );
    if(ok){
        load(d->currentProjectPath.getPath());
    }
}

void Project::load(const QString& path)
{
    d->load(path);
    emit wasReplaced(path);
}

#include <QAction>
void Project::load(QAction* action)
{
    d->currentProjectPath.setPath(action->data().toString());
    reload();
}

void Project::reload()
{
    if(d->currentProjectPath.isEmpty()){
        load();
    }
    else{
        load(d->currentProjectPath.getPath());
    }
}

void Project::close()
{
    d->close();
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
        static_cast<QWidget*>(this->parent()),
        tr("Open project")
     );
    if(ok){
        d->save(d->currentProjectPath.getPath());
        emit wasReplaced(d->currentProjectPath.getPath());
    }
    return ok;
}
