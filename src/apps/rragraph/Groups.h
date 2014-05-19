#ifndef GROUPS_H
#define GROUPS_H

class Path;
class QMdiSubWindow;
class Group;
class PlotSettingsFiller;
#include <QTabWidget>
#include <Path.h>

class Groups : public QTabWidget
{
    Q_OBJECT
public:
    explicit Groups(QWidget* parent = 0);
    void processArgs(const QStringList& args);
public slots:
    Group* addGroup();
    void closeGroups();
    void clearActiveGroup();
    void tileActiveGroup();
    void addPlot();
    void exportActiveGroupToPng();
    void exportToPng();
    void exportActiveGroupToPdf();
    void autoScaleActiveGroup();
    void setGroupTiling(QAction* action);
    void retitle();
    Group* getGroup() const;
    Group* getGroup(int i) const;
    void serialize(QJsonObject& root, const Path& proPath) const;
    void restore(const QJsonObject& root, const Path& proPath);
    void retranslate();
    void activate();
    Group* toDefaultState();
    void copySettingsToActiveGroup(PlotSettingsFiller* filler);
signals:
    void hasGroups(bool);
    void noMoreGroup();
    void noMorePlots();
    void groupChanged(Group* plots);
    void wasActivated(QMdiSubWindow*);
    void beginExport();
    void endExport();
private slots:
    void tryCloseGroup(int i);
    void closeGroup(int i);
    void createGroupChangedSignal(int i);
    void emitAboutActiveGroup(Group *group);
private:
    void setStyles();
    void setLookAndFeel();
};

#endif // GROUPS_H
