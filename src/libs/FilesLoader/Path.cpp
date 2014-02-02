#include "Path.h"
#include <QDebug>
#include <QSettings>

Path::Path(const QString& settingsFilePath, const QString& settingsKey):
    settingsKey(settingsKey),
    settingsFilePath(settingsFilePath)
{    
    path = QSettings(settingsFilePath, QSettings::IniFormat) .value(settingsKey).toString();
}

Path::~Path()
{
    if(!path.isEmpty()){
        QSettings(settingsFilePath, QSettings::IniFormat).setValue(settingsKey, path);
    }
}

QFileInfo Path::getPathInfo() const
{
    return QFileInfo(path);
}

#include <QFileDialog>
QStringList Path::getOpenFileNames(QWidget* parent, const QString& comment, const QString& filesFilter)
{
   QStringList openFileNames = QFileDialog::getOpenFileNames(parent, comment, path, filesFilter);
   if(!openFileNames.isEmpty()){
       update(openFileNames[0]);
   }
   return openFileNames;
}

QString Path::getOpenFileName(QWidget* parent, const QString& comment, const QString& filesFilter)
{
    QString openFileName = QFileDialog::getOpenFileName(parent, comment, path, filesFilter);
    updateIfExist(openFileName);
    return openFileName;
}

QString Path::getExistingDirectory(QWidget* parent, const QString& comment)
{
    QString dir = QFileDialog::getExistingDirectory(parent, comment, path);
    updateIfExist(dir);
    return dir;
}

void Path::updateIfExist(const QString& path)
{
    if(!path.isEmpty()){
        update(path);
    }
}

void Path::update(const QString& path)
{
    this->path = path;
}
