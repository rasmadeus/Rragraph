#include "ExitMessage.h"
#include "ui_ExitMessage.h"

ExitMessage::ExitMessage(QWidget *parent) :
    AskMessage("ExitMessageGeometry", parent),
    ui(new Ui::ExitMessage)
{
    ui->setupUi(this);
    connect(ui->yes,    SIGNAL(clicked()), SLOT(yes()));
    connect(ui->no,     SIGNAL(clicked()), SLOT(no()));
    connect(ui->cancel, SIGNAL(clicked()), SLOT(cancel()));
}

ExitMessage::~ExitMessage()
{
    delete ui;
}

void ExitMessage::yes()
{
    aboutClose(SAVE_PROJECT_AND_EXIT);
}

void ExitMessage::no()
{
    aboutClose(DO_NOT_SAVE_PROJECT_AND_EXIT);
}

void ExitMessage::cancel()
{
    aboutClose(GO_BACK);
}
