#ifndef PLOTSGROUPS_H
#define PLOTSGROUPS_H

class Group;
#include <QTabWidget>

class PlotsGroups : public QTabWidget
{
    Q_OBJECT
public:
    explicit PlotsGroups(QWidget* parent = 0);
public slots:
    void addPlots();
    void closeGroups();
    void clearActiveGroup();
    void tileActiveGroup();
    void addPlot();
    void exportActiveGroup();
    void autoScaleActiveGroup();
    void setGroupTiling(QAction* action);
signals:
    void hasGroups(bool);
    void groupChanged(Group* plots);
private slots:
    void closeGroup(int i);
    void createGroupChangedSignal(int i);
private:
    Group* getGroup() const;
    void setStyles();
    void setLookAndFeel();
    void retitle();
    QVector<Group*> groups;
};

#endif // PLOTSGROUPS_H1
