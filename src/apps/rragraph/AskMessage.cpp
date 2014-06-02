#include "AskMessage.h"

#include <Settings.h>
#include <QApplication>
AskMessage::AskMessage(const QString& dialogKey, QWidget *parent) :
    QDialog(parent),
    order(0)
{
    this->dialogKey = "widgets/" + dialogKey;
    restoreGeometry(Settings::obj()->get(this->dialogKey).toByteArray());
}

AskMessage::~AskMessage()
{
   Settings::obj()->set(dialogKey, saveGeometry());
}

int AskMessage::exec()
{
    QDialog::exec();
    return order;
}

void AskMessage::aboutClose(int order)
{
    this->order = order;
    close();
}
