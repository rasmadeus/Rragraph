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
    explicit GroupSettings(QWidget* parent = 0);
    ~GroupSettings();
    void retranslate();
public slots:
    void catchGroup(Group* group);
    void freeGroup();
signals:
    void groupNameWasChanged();
private slots:
    void setGroupName();
private:    
    void setDefaultGroupName();
    Ui::GroupSettings *ui;
    Group* group;
};

#endif // GROUPSETTINGS_H
