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
    static bool messageIsVisible();
    int exec();
public slots:
    static void setMessageVisible(bool isVisible);
private slots:
    void yes();
    void no();
    void cancel();
    void unvisibleMessage();
private:
    Order order;
    Ui::ExitMessage *ui;
};

#endif // EXITMESSAGE_H
