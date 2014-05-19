#include "Path.h"

QString Path::getTemplate(Templates type)
{
    static const char* templates[] = {
        QT_TR_NOOP("All files (*)")
    };
    switch(type){
         case ALL_FILES: return QObject::tr(templates[0]);
         default:        return QObject::tr(templates[0]);
    }
}

Path::Path(const QString& settingsKey):
    settingsKey(settingsKey)
{
}

#include <Settings.h>
Path::~Path()
{
    if(!path.isEmpty()){
        Settings::obj()->set(settingsKey, path);
    }
}

QString Path::getLastPath() const
{
    return path.isEmpty()                                                                ?
        Settings::obj()->get(settingsKey).toString() :
        path;
}

QFileInfo Path::getPathInfo() const
{
    return QFileInfo(path);
}

#include <QFileDialog>
QStringList Path::getOpenFileNames(QWidget* parent, const QString& comment, const QString& filesFilter)
{
   QStringList openFileNames = QFileDialog::getOpenFileNames(parent, comment, getLastPath(), filesFilter);
   if(!openFileNames.isEmpty()){
       update(openFileNames.first());
   }
   return openFileNames;
}

bool Path::setOpenFileName(QWidget* parent, const QString& comment, const QString& filesFilter)
{
    QString openFileName = QFileDialog::getOpenFileName(parent, comment, getLastPath(), filesFilter);
    return updateIfExist(openFileName);
}

bool Path::setSaveFileName(QWidget* parent, const QString& comment, const QString& filter)
{
    QString saveFileName = QFileDialog::getSaveFileName(parent, comment, getLastPath(), filter);
    return updateIfExist(saveFileName);
}

bool Path::setExistingDirectory(QWidget* parent, const QString& comment)
{
    QString dir = QFileDialog::getExistingDirectory(parent, comment, getLastPath());
    return updateIfExist(dir);
}

bool Path::updateIfExist(const QString& path)
{
    const bool isEmpty = path.isEmpty();
    if(!isEmpty){
        update(path);
        return true;
    }
    return false;
}

void Path::update(const QString& path)
{
    this->path = path;
}

bool Path::isEmpty() const
{
    return path.isEmpty();
}

const QString& Path::getPath() const
{
    return path;
}

void Path::setPath(const QString& path)
{
    this->path = path;
}

QString Path::getRelativePath(const QString& absolutePath) const
{
    return getPathInfo().absoluteDir().relativeFilePath(absolutePath);
}

QString Path::getAbsolutePath(const QString& relativePath) const
{
    return getPathInfo().absoluteDir().absoluteFilePath(relativePath);
}

void Path::clear()
{
    path = "";
}
