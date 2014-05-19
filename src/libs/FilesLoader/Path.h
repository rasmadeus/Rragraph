#ifndef PATH_H
#define PATH_H

class QApplication;
#include <QString>
#include <QFileInfo>

class Path
{
public:
    enum Templates
    {
        ALL_FILES
    };
    static QString getTemplate(Templates type);

    Path(const QString& settingsKey);
    ~Path();
    QFileInfo getPathInfo() const;
    QStringList getOpenFileNames(QWidget* parent, const QString& comment, const QString& filesFilter = QString());
    bool setOpenFileName(QWidget* parent, const QString& comment, const QString& filesFilter = QString());
    bool setSaveFileName(QWidget* parent, const QString& comment, const QString& filter = QString());
    bool setExistingDirectory(QWidget* parent, const QString& comment);
    bool isEmpty() const;
    const QString& getPath() const;
    void setPath(const QString& path);
    QString getRelativePath(const QString& absolutePath) const;
    QString getAbsolutePath(const QString& relativePath) const;
    void clear();
private:
    bool updateIfExist(const QString& path);
    void update(const QString& path);
    QString getLastPath() const;
    QString path;
    QString settingsKey;
    QString settingsFilePath;
};

#endif // PATH_H
