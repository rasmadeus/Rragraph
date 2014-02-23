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
//3.
    restoreGeometry(QSettings("appSettings.ini", QSettings::IniFormat).value("widgets/ExitMessageGeometry").toByteArray());
}

ExitMessage::~ExitMessage()
{
    QSettings("appSettings.ini", QSettings::IniFormat).setValue("widgets/ExitMessageGeometry", saveGeometry());
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
