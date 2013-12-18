#ifndef MANAGER_H
#define MANAGER_H

class SamplesManager;
class SamplesQListModel;
class QQmlContext;
#include <QObject>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QQmlContext* rootContext, QObject* root, QObject* parent = 0);
signals:
private slots:
    void loadData();
private:
    QQmlContext* rootContext;
    SamplesManager* samplesManager;
    SamplesQListModel* samplesModel;
    QObject* root;
        QObject* windowsModel;
            QObject* data;
};

#endif // MANAGER_H
