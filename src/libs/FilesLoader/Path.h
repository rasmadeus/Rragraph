#ifndef PATH_H
#define PATH_H

class QApplication;
#include <QString>
#include <QFileInfo>

class Path
{
public:
    Path(const QString& settingsFilePath, const QString& settingsKey);
    ~Path();
    QFileInfo getPathInfo() const;
    QStringList getOpenFileNames(QWidget* parent, const QString& comment, const QString& filesFilter = QString());
    QString getOpenFileName(QWidget* parent, const QString& comment, const QString& filesFilter = QString()); 
    QString getExistingDirectory(QWidget* parent, const QString& comment);
private:
    void updateIfExist(const QString& path);
    void update(const QString& path);
    QString path;
    QString settingsKey;
    QString settingsFilePath;
};

#endif // PATH_H
