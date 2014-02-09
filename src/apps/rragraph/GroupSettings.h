#ifndef GROUPSETTINGS_H
#define GROUPSETTINGS_H

class Group;
#include <QWidget>

namespace Ui {
class GroupSettings;
}

class GroupSettings : public QWidget
{
    Q_OBJECT
public:
    explicit GroupSettings(QWidget *parent = 0);
    ~GroupSettings();
    void setGroup(Group* group);
signals:
    void groupNameWasChanged();
private slots:
    void setGroupName(const QString& name);
private:
    Ui::GroupSettings *ui;
    Group* group;
};

#endif // GROUPSETTINGS_H
