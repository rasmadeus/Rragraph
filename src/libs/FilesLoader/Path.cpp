#include "Path.h"
#include <QDebug>
#include <QSettings>

Path::Path(const QString& settingsFilePath, const QString& settingsKey):
    settingsKey(settingsKey),
    settingsFilePath(settingsFilePath)
{
}

Path::~Path()
{
    if(!path.isEmpty()){
        QSettings(settingsFilePath, QSettings::IniFormat).setValue(settingsKey, path);
    }
}

QString Path::getLastPath() const
{
    return path.isEmpty()                                                                ?
        QSettings(settingsFilePath, QSettings::IniFormat) .value(settingsKey).toString() :
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

bool Path::setSaveFileName(QWidget* parent, const QString& comment)
{
    QString saveFileName = QFileDialog::getSaveFileName(parent, comment, getLastPath());
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
