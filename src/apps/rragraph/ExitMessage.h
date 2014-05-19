#ifndef EXITMESSAGE_H
#define EXITMESSAGE_H

#include "AskMessage.h"

namespace Ui {
class ExitMessage;
}

class ExitMessage : public AskMessage
{
    Q_OBJECT
public:
    enum Order
    {
        SAVE_PROJECT_AND_EXIT,
        DO_NOT_SAVE_PROJECT_AND_EXIT,
        GO_BACK
    };
    explicit ExitMessage(QWidget* parent = 0);
    ~ExitMessage();
private slots:
    void yes();
    void no();
    void cancel();
private:
    Ui::ExitMessage *ui;
};

#endif // EXITMESSAGE_H
