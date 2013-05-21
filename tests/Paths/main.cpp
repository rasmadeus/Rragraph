#include <QApplication>

#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QStringList>


void show(const QStringList& sl){
    foreach(QString string, sl)
        qDebug() << string;
}


QString parsing(const QString& project_path, const QString& file_path){
    QString result;

    QStringList project_parts = project_path.split("/");
    QStringList file_parts = file_path.split("/");

    project_parts.removeLast();
    file_parts.removeLast();

    while(project_parts.size() && file_parts.size()){
        if(project_parts.first() == file_parts.first()){
            project_parts.removeFirst();
            file_parts.removeFirst();
        }
        else{
            break;
        }
    }

    for(int i=0; i<project_parts.size(); ++i){
        result.append("../");
    }
    for(int i=0; i<file_parts.size(); ++i){
        result.append(file_parts[i]);
        result.append("/");
    }
    result.append(QFileInfo(file_path).fileName());

    return result;
}


int main(int argc, char** argv){
    QApplication Paths(argc, argv);
    QString project_path = "C:/Dev/Super Papka/project.rgf";
    QString file_1       = "C:/Dev/file_1.txt";
    QString file_2       = "C:/Dev/Super Papka/Vasya/file_2.txt";
    QString file_3       = "C:/Dev/habrahabr/file_3.txt";
    QString file_4       = "F:/file_4.txt";
    QString file_5       = "C:/Dev/Super Papka/file_5.txt";
    QString relative_path = "../../file.txt";
    QString absolute_path = "/dir/file.txt";
    QString relative_two = "dir/file.txt";

//    qDebug() << parsing(project_path, file_5);

    QFileInfo fi(project_path);
    qDebug() << fi.isRelative() << fi.isAbsolute();
    QFileInfo fi2(relative_path);
    qDebug() << fi2.isRelative() << fi2.isAbsolute();
    QFileInfo fi3(absolute_path);
    qDebug() << fi3.isRelative() << fi3.isAbsolute();
    QFileInfo fi4(relative_two);
    qDebug() << fi4.isRelative() << fi4.isAbsolute();
//    qDebug() << "absoluteDir " << fi.absoluteDir();
//    qDebug() << "absoluteFilePath " << fi.absoluteFilePath();
//    qDebug() << "absolutePath " << fi.absolutePath();
//    qDebug() << "baseName " << fi.baseName();
//    qDebug() << "bundleName " << fi.bundleName();
//    qDebug() << "canonicalFilePath " << fi.canonicalFilePath();
//    qDebug() << "canonicalPath " << fi.canonicalPath();
//    qDebug() << "completeBaseName " << fi.completeBaseName();
//    qDebug() << "completeSuffix " << fi.completeSuffix();
//    qDebug() << "group " << fi.group();
//    qDebug() << "makeAbsolute" << fi.makeAbsolute();

    return Paths.exec();
}
