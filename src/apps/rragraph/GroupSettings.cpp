#include "GroupSettings.h"
#include "ui_GroupSettings.h"

GroupSettings::GroupSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupSettings)
{
    ui->setupUi(this);
    connect(ui->groupName, SIGNAL(textChanged(QString)), SLOT(setGroupName(QString)));
    setEnabled(false);
}

GroupSettings::~GroupSettings()
{
    delete ui;
}

void GroupSettings::retranslate()
{
    ui->retranslateUi(this);
}

#include "Group.h"
void GroupSettings::setGroupName(const QString& name)
{
    group->setName(name);
    emit groupNameWasChanged();
}

void GroupSettings::setGroup(Group* group)
{
    this->group = group;
    ui->groupName->setText(group->getName());
    setEnabled(true);
}
