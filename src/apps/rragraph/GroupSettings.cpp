#include "GroupSettings.h"
#include "ui_GroupSettings.h"

GroupSettings::GroupSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupSettings)
{
    ui->setupUi(this);
    connect(ui->groupName, SIGNAL(editingFinished()), SLOT(setGroupName()));
    freeGroup();
}

GroupSettings::~GroupSettings()
{
    delete ui;
}

void GroupSettings::retranslate()
{
    ui->retranslateUi(this);
    setDefaultGroupName();
}

#include "Group.h"
void GroupSettings::setGroupName()
{
    if(group){ //Условие нужно, так как из-за freeGroup() генерируется сигнал textChanged.
        group->setName(ui->groupName->text());
        emit groupNameWasChanged();
    }
}

void GroupSettings::catchGroup(Group* group)
{
    this->group = group;
    ui->groupName->setText(group->getName());
    setEnabled(true);
}

void GroupSettings::freeGroup()
{
    setEnabled(false);
    this->group = nullptr;
    setDefaultGroupName();
}

void GroupSettings::setDefaultGroupName()
{
    if(!group){
        ui->groupName->setText(tr("It isn't active group"));
    }
}
