#ifndef GROUPS_H
#define GROUPS_H

class Path;
class QMdiSubWindow;
class Group;
#include <QTabWidget>
#include <Path.h>

class Groups : public QTabWidget
{
    Q_OBJECT
public:
    explicit Groups(QWidget* parent = 0);
public slots:
    Group* addGroup();
    void closeGroups();
    void clearActiveGroup();
    void tileActiveGroup();
    void addPlot();
    void exportActiveGroupToPng();
    void exportToPng();
    void autoScaleActiveGroup();
    void setGroupTiling(QAction* action);
    void retitle();
    Group* getGroup() const;
    void serialize(QJsonObject& root, const Path& proPath) const;
    void restore(const QJsonObject& root, const Path& proPath);
    void retranslate();
signals:
    void hasGroups(bool);
    void noMoreGroup();
    void groupChanged(Group* plots);
    void wasActivated(QMdiSubWindow*);
private slots:
    void closeGroup(int i);
    void createGroupChangedSignal(int i);
private:
    void setStyles();
    void setLookAndFeel();
    QVector<Group*> groups;
    static Path exportPath;
};

#endif // GROUPS_H
