#ifndef PROJECT_H
#define PROJECT_H

#include "RestorablePath.h"
#include <QObject>
#include <QJsonDocument>

class Project : public QObject
{
    Q_OBJECT
    RestorablePath lastPath;
    QJsonDocument doc;
public:
    explicit Project(QObject* parent = 0);
public slots:
    void load();
    void saveAs();
    void reload();
    void resave();
private:
    void showLoadingError();
    void showSavingError();
    void fillProject();
    void applyProject();
};

#endif // PROJECT_H
