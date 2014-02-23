#ifndef EXITMESSAGE_H
#define EXITMESSAGE_H

#include <QDialog>

namespace Ui {
class ExitMessage;
}

class ExitMessage : public QDialog
{
    Q_OBJECT
public:
    enum Order
    {
        SAVE_PROJECT_AND_EXIT,
        DO_NOT_SAVE_PROJECT_AND_EXIT,
        GO_BACK
    };
    explicit ExitMessage(QWidget *parent = 0);
    ~ExitMessage();
    int exec();
private slots:
    void yes();
    void no();
    void cancel();
private:
    Order order;
    Ui::ExitMessage *ui;
};

#endif // EXITMESSAGE_H
