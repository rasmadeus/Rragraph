#ifndef FILEPATHPARSING_H
#define FILEPATHPARSING_H

class QString;

class FilePathParsing
{
public:
    static QString getRelativePath(const QString& from, const QString& to);
    //For example:
    //from = /dir/file.txt
    //to = C:/texts
    //absolute_path(from, to) = C:/texts/dir/file.txt;
    static QString getAbsolutePath(const QString from, const QString& to);
};

#endif // FILEPATHPARSING_H
