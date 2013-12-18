#include "Project.h"

SINGLETON_IMPLEMENTATION(Project, QObject)

#include "Files.h"
Project::Project(QObject* parent) :
    QObject(parent),
    lastPath("lastProjectPath")
{
    connect(Files::getInstance(), SIGNAL(wasLoaded(int)), SLOT(wasLoaded(int)));
}

const RestorablePath& Project::getPath() const{
    return lastPath;
}

#include <QDir>
QDir Project::getProjectDir() const{
    return lastPath.getInfoPath().absoluteDir();
}

#include <QFileDialog>
void Project::load()
{
    QString path = QFileDialog::getOpenFileName(
        static_cast<QWidget*>(parent()),
        tr("Open a project"),
        lastPath(),
        tr("Rragraph file(*.rgf);;All files(*)")
    );
    if(!path.isEmpty()){
        clearWindowsAndFiles();
        lastPath = path;
        reloadPath();
    }
}

#include <QApplication>
void Project::loadFromArgs()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    load(args);
}

#include "MdiArea.h"
void Project::load(const QStringList& paths)
{
    if(paths.isEmpty()){
        return;
    }
    auto i = std::find_if(
        paths.constBegin(),
        paths.constEnd(),
        [](const QString& path){return QFileInfo(path).suffix() == "rgf";}
    );
    if(i == paths.constEnd()){
        Files::getInstance()->load(paths);
    }
    else{
        close();
        lastPath = *i;
        reloadPath();
    }
    MdiArea::getInstance()->tile();
}

bool Project::save()
{
    if(lastPath.getPath().isEmpty()){
        return saveAs();
    }
    else{
        return resave();
    }
}

void Project::reload()
{
    if(lastPath.getPath().isEmpty()){
        load();
    }
    else{
        clearWindowsAndFiles();
        reloadPath();
    }
}


#include "CurveSettingsView.h"
void Project::clearWindowsAndFiles()
{
    CurveSettingsView::getInstance()->setOwner(nullptr);
    MdiArea::getInstance()->closeAllSubWindows();
    Files::getInstance()->removeAll();
}

void Project::close()
{
    clearWindowsAndFiles();
    lastPath.clearPath();
    doc = QJsonDocument();
    emit wasClosed(tr("Rragraph")); //Set title to MainWindow
}

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
void Project::reloadPath()
{
    QFile file(lastPath.getPath());
    if(!file.open(QFile::ReadOnly)){
        lastPath.clearPath();
        showLoadingError();
        return;
    }    
    doc = QJsonDocument::fromJson(file.readAll());
    applyProject();
    emit wasLoadedFrom(lastPath.getPath());
    ifSaveLastPathToSettings();
}

#include <QDir>
#include <QAction>
void Project::loadProjectFrom(QAction* action)
{
    lastPath = action->data().toString();
    clearWindowsAndFiles();
    reloadPath();
}

bool Project::resave()
{
    QFile file(lastPath.getPath());
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        showSavingError();
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    fillProject();
    out << doc.toJson(QJsonDocument::Indented);
    emit wasSavedAs(lastPath.getPath());
    return true;
}

bool Project::saveAs()
{
    const QString path = QFileDialog::getSaveFileName(
            static_cast<QWidget*>(parent()),
            tr("Save this project as"),
            lastPath(),
            tr("Rragraph file(*.rgf)")
        );
    if(!path.isEmpty()){
        lastPath = path;
        bool ok = resave();
        ifSaveLastPathToSettings();
        return ok;
    }   
    return false;
}

#include <QJsonObject>
#include <QJsonArray>
#include "HeaderSamples.h"
void Project::fillProject()
{
    QJsonObject root;
    MdiArea::getInstance()->serialize(root);
    MdiArea::getInstance()->serializeCurves(root);
    Files::getInstance()->serialize(root);
    HeaderSamples::getInstance()->serialize(root);
    doc.setObject(root);
}

void Project::wasLoaded(int iFile)
{
    MdiArea::getInstance()->restoreCurves(iFile, doc.object());
    HeaderSamples::getInstance()->restore(iFile, doc.object());
    if(iFile == Files::getInstance()->countSamples() - 1){
        doc = QJsonDocument();
    }
}

void Project::applyProject()
{
    QJsonObject root = doc.object();
    MdiArea::getInstance()->restore(root);
    Files::getInstance()->restore(root);
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

#include <QSettings>
#include <QStringList>
static void fillPaths(QSettings& s, QStringList& paths)
{
    int n = s.beginReadArray("LastProjectPaths");
    for(int i = 0; i < n; ++i){
        s.setArrayIndex(i);
        QString path = s.value("path").toString();
        if(QFileInfo(path).exists()){
            paths.push_back(s.value("path").toString());
        }
        else{
            s.remove("path");
        }
    }
    s.endArray();
}

static void rearrangePaths(QStringList& paths, const QString& path)
{
    if(paths.contains(path)){
        paths.removeOne(path);
    }
    if(paths.size() > 4){
        paths.removeLast();
    }
    paths.insert(0, path);
}

static void savePathsTo(QSettings& s, QStringList& paths)
{
    s.beginWriteArray("LastProjectPaths");
    for(int i = 0; i < paths.size(); ++i){
        s.setArrayIndex(i);
        s.setValue("path", paths[i]);
    }
    s.endArray();
}

void Project::ifSaveLastPathToSettings()
{
    QSettings s;
    QStringList paths;
    fillPaths(s, paths);
    rearrangePaths(paths, lastPath.getPath());
    savePathsTo(s, paths);
    emit lastLoadedPathsChanged();
}

QStringList Project::lastLoadedPaths() const
{
    QStringList paths;
    QSettings s;
    fillPaths(s, paths);
    return paths;
}

void Project::copyProjectFile()
{
    if(lastPath.getPath().isEmpty()){
        QMessageBox::warning(
            static_cast<QWidget*>(parent()),
            tr("Copy error"),
            tr("You have to open a project!")
        );
        return;
    }
    QString newPath = QFileDialog::getSaveFileName(
        static_cast<QWidget*>(parent()),
        tr("New name"),
        lastPath()
    );
    if(!newPath.isEmpty()){
        QFile newFile(newPath);
        if(newFile.remove()){
            newFile.close();
            QFile currentFile(lastPath.getPath());
            if(currentFile.copy(newPath)){
                clearWindowsAndFiles();
                lastPath = newPath;
                reloadPath();
                return;
            }
        }
        QMessageBox::warning(
            static_cast<QWidget*>(parent()),
            tr("Copy error"),
            tr("It's impossible to copy the project's file!")
        );
    }
}
