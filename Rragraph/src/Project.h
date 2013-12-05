#ifndef PROJECT_H
#define PROJECT_H

class QDir;
class QAction;
#include "global.h"
#include "RestorablePath.h"
#include <QObject>
#include <QJsonDocument>

class Project : public QObject
{
    Q_OBJECT
    SINGLETON_HEADER(Project, QObject)
public slots:
    void load();
    bool save();
    bool saveAs();
    void reload();
    void close();
    void loadProjectFrom(QAction* action);
    void copyProjectFile();
public:
    const RestorablePath& getPath() const;
    QDir getProjectDir() const;
    QStringList lastLoadedPaths() const;
    void load(const QStringList& paths);
    void loadFromArgs();
signals:
    void wasLoadedFrom(const QString& path);
    void wasSavedAs(const QString& path);
    void wasClosed(const QString& path);
    void lastLoadedPathsChanged();
private slots:
    void wasLoaded(int iFile);
private:
    void ifSaveLastPathToSettings();
    void clearWindowsAndFiles();
    bool resave();
    void reloadPath();
    void showLoadingError();
    void showSavingError();
    void fillProject();
    void applyProject();
    RestorablePath lastPath;
    QJsonDocument doc;
};

#endif // PROJECT_H
