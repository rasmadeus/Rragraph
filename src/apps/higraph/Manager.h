#ifndef MANAGER_H
#define MANAGER_H

class SamplesManager;
class QQmlContext;
#include <QObject>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QQmlContext* rootContext, QObject* root, QObject* parent = 0);
private slots:
    void loadData();
    void haveBeenLoaded(int i);
    void move(int pos);
    void moveAllToMoverPos();
private:
    bool firstFileWasLoaded;
    QQmlContext* rootContext;
    SamplesManager* samplesManager;
    QObject* root;
        QObject* windowsModel;
            QObject* histogram;
                QObject* mover;
                QObject* firstFileTime;
                QObject* sliceMaxValue;
};

#endif // MANAGER_H
