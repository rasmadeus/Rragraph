#ifndef YESNOMESSAGE_H
#define YESNOMESSAGE_H

#include "AskMessage.h"

namespace Ui {
class YesNoMessage;
}

class YesNoMessage : public AskMessage
{
    Q_OBJECT    
public:
    enum Order
    {
        YES,
        NO
    };
    explicit YesNoMessage(const QString& action, QWidget* parent = 0);
    ~YesNoMessage();
    static void proxyAction(QWidget* parent, bool ok, const QString& actionName, const std::function<void()>& action)
    {
        if (ok){
            YesNoMessage doAction(actionName, parent);
            switch(doAction.exec()){
                case YesNoMessage::YES: action(); return;
                case YesNoMessage::NO: return;
            }
        }
        else{
            action();
        }
    }
private slots:
    void yes();
    void no();
private:
    Ui::YesNoMessage *ui;
};

#endif // YESNOMESSAGE_H
