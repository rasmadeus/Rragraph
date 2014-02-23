#ifndef PROJECT_H
#define PROJECT_H

class QAction;
class QActionGroup;
class Groups;
#include <QObject>

class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(Groups* groups, QWidget* parent);
    ~Project();
    void load(const QString& path);
public slots:
    void load();
    void load(QAction* action);
    void reload();
    void close();
    bool save();
    bool saveAs();
signals:
    void wasReplaced(const QString& path);
    void wasClosed();
private:
    class ProjectPrivateData;
    ProjectPrivateData* d;
};

#endif // PROJECT_H
