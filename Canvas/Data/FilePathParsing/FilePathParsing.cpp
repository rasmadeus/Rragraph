#include "FilePathParsing.h"

#include <QString>
#include <QStringList>
#include <QFileInfo>
QString FilePathParsing::getRelativePath(const QString &from, const QString &to)
{
    QString result;
    //To split paths to the elements.
    QStringList fromParts = from.split("/");
    QStringList toParts = to.split("/");
    if(fromParts.isEmpty() || toParts.isEmpty()) return result;
    //Delete file name.
    fromParts.removeLast();
    toParts.removeLast();
    //If the first elements is not equals then "to" is in another drive.
    if(fromParts.first() != toParts.first()){
        return to;
    }
    //Delete the same parts.
    while(fromParts.size() && toParts.size()){
        if(fromParts.first() == toParts.first()){
            fromParts.removeFirst();
            toParts.removeFirst();
        }
        else{
            break;
        }
    }
    //If from_parts is not empty we get up result in hierarhy.
    for(int i=0; i<fromParts.size(); ++i){
        result.append("../");
    }
    //Add dirs.
    for(int i=0; i<toParts.size(); ++i){
        result.append(toParts[i]);
        result.append("/");
    }
    //Add file_name.
    result.append(QFileInfo(to).fileName());
    //The result is prepared!
    return result;
}

//For example:
//from = /dir/file.txt
//to = C:/texts
//absolute_path(from, to) = C:/texts/dir/file.txt;
QString FilePathParsing::getAbsolutePath(const QString from, const QString &to)
{
    if(QFileInfo(from).isAbsolute()) return from;
    QString result;
    //To split the parts.
    QStringList fromParts = from.split("/");
    QStringList toParts = to.split("/");
    //Remove project name;
    if(toParts.isEmpty()) return result;
    toParts.removeLast();
    //To level the hierarhy.
    while(fromParts.size() && toParts.size()){
        if(fromParts.first() == ".."){
            fromParts.removeFirst();
            toParts.removeLast();
        }
        else{
            break;
        }
    }
    //To stick together the parts.
    for(int i=0; i<toParts.size(); ++i){
        result.append(toParts[i]);
        result.append("/");
    }
    for(int i=0; i<fromParts.size(); ++i){
        result.append(fromParts[i]);
        if(i < fromParts.size() - 1) result.append("/");
    }
    //The result is prepared!
    return result;
}
