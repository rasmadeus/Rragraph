#ifndef ASKMESSAGE_H
#define ASKMESSAGE_H

#include <QDialog>

class AskMessage : public QDialog
{
    Q_OBJECT
public:
    explicit AskMessage(const QString& dialogKey, QWidget* parent = 0);
    ~AskMessage();
    int exec();
protected:
    void aboutClose(int order);
    int order;
    QString dialogKey;
};

#endif // ASKMESSAGE_H
