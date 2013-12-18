#include "ExitMessage.h"
#include "ui_ExitMessage.h"

#include <QSettings>
ExitMessage::ExitMessage(QWidget *parent) :
    QDialog(parent),
    order(GO_BACK),
    ui(new Ui::ExitMessage)
{
//1.
    ui->setupUi(this);
//2.
    connect(ui->yes,       SIGNAL(clicked()),     SLOT(yes()));
    connect(ui->no,        SIGNAL(clicked()),     SLOT(no()));
    connect(ui->cancel,    SIGNAL(clicked()),     SLOT(cancel()));
    connect(ui->isShow,    SIGNAL(clicked(bool)), SLOT(setMessageVisible(bool)));
//3.
    restoreGeometry(QSettings().value("ExitMessage/geometry").toByteArray());
}

void ExitMessage::setMessageVisible(bool isVisible){
    QSettings().setValue("ExitMessage/isShow", isVisible);
}

bool ExitMessage::messageIsVisible(){
    return QSettings().value("ExitMessage/isShow", true).toBool();
}

ExitMessage::~ExitMessage()
{
    QSettings().setValue("ExitMessage/geometry", saveGeometry());
    delete ui;
}

int ExitMessage::exec()
{
    QDialog::exec();
    return order;
}

void ExitMessage::yes()
{
    order = SAVE_PROJECT_AND_EXIT;
    close();
}

void ExitMessage::no()
{
    order = DO_NOT_SAVE_PROJECT_AND_EXIT;
    close();
}

void ExitMessage::cancel()
{
    order = GO_BACK;
    close();
}

void ExitMessage::unvisibleMessage(){
    setMessageVisible(false);
}
