#include "YesNoMessage.h"
#include "ui_YesNoMessage.h"

YesNoMessage::YesNoMessage(const QString& action, QWidget *parent) :
    AskMessage("YesNoMessage", parent),
    ui(new Ui::YesNoMessage)
{
    ui->setupUi(this);
    ui->label->setText("<center>" + tr("Do you really want to ") + action + "</center>");
    connect(ui->yes, SIGNAL(clicked()), SLOT(yes()));
    connect(ui->no, SIGNAL(clicked()), SLOT(no()));
}

YesNoMessage::~YesNoMessage()
{
    delete ui;
}

void YesNoMessage::yes()
{
    aboutClose(YES);
}

void YesNoMessage::no()
{
    aboutClose(NO);
}
