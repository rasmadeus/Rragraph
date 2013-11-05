#include "RestorablePath.h"

RestorablePath::RestorablePath(const QString& key):
    key(key){
}

void RestorablePath::operator = (const QString& path){
    this->path = path;
}

#include <QSettings>
RestorablePath::~RestorablePath()
{
    if(!path.isEmpty()){
        QSettings s;
        s.setValue(key, path);
    }
}

QString RestorablePath::operator ()(){
    if(path.isEmpty()){
        QSettings s;
        return s.value(key).toString();
    }
    return path;
}

QFileInfo RestorablePath::getInfoPath() const{
    return QFileInfo(path);
}

const QString& RestorablePath::getPath() const{
    return path;
}

void RestorablePath::clearPath(){
    path = "";
}
