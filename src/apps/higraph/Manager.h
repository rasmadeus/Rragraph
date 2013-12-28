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
    explicit Manager(QObject* root, QObject* parent = 0);
private slots:
    void loadData();
    void haveBeenLoaded(int i);
    void move(int pos);
    void moveAllToMoverPos();
    void resetFileLoadingFlag();
    void start();
    void moveAllFurther();
private:
    static const int COUNT_MS_FOR_UPDATING = 150;
    bool firstFileWasLoaded;
    QTimer* timer;
    SamplesManager* samplesManager;
    QObject* findObject(QObject* parent, const QString& childName);
    void findObjects();
    QObject* root;
        QObject* menu;
            QObject* starter;
        QObject* windowsModel;
            QObject* histogram;
                QObject* mover;
                QObject* sliceTime;
                QObject* numberSliceMaxValue;
                QObject* sliceMaxValue;
                QObject* sliceAverage;
};

#endif // MANAGER_H
