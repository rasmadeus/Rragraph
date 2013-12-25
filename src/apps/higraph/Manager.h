#ifndef MANAGER_H
#define MANAGER_H

class SamplesManager;
class QQmlContext;
class QTimer;
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
    void resetFileLoadingFlag();
    void start();
    void incAll();
private:
    bool firstFileWasLoaded;
    QTimer* timer;
    QQmlContext* rootContext;
    SamplesManager* samplesManager;
    QObject* root;
        QObject* windowsModel;
            QObject* histogram;
                QObject* mover;
                QObject* starter;
                QObject* firstFileTime;
                QObject* sliceMaxValue;
};

#endif // MANAGER_H
