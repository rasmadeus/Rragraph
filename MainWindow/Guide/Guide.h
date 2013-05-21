#ifndef GUIDE_H
#define GUIDE_H

class QAction;

#include <QThread>
#include <QUrl>

class Guide : public QThread
{
    Q_OBJECT
public:
    explicit Guide(QObject *parent = 0);
    void setUrl(QAction* action);
protected:
    void run();
signals:
    void dataWasShowed();
private:
    QUrl url;
};

#endif // GUIDE_H
