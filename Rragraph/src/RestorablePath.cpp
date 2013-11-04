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
        path = s.value(key).toString();
    }
    return path;
}

