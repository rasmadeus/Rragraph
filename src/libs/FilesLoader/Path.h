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
    bool setOpenFileName(QWidget* parent, const QString& comment, const QString& filesFilter = QString());
    bool setSaveFileName(QWidget* parent, const QString& comment);
    bool setExistingDirectory(QWidget* parent, const QString& comment);
    bool isEmpty() const;
    const QString& getPath() const;
    void setPath(const QString& path);
    QString getRelativePath(const QString& absolutePath) const;
    QString getAbsolutePath(const QString& relativePath) const;
private:
    bool updateIfExist(const QString& path);
    void update(const QString& path);
    QString getLastPath() const;
    QString path;
    QString settingsKey;
    QString settingsFilePath;
};

#endif // PATH_H
