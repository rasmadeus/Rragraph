#ifndef CONSUMER_H
#define CONSUMER_H

class Samples;
#include <QThread>

class Consumer : public QThread
{
    Q_OBJECT
public:
    explicit Consumer(Samples* samples, QObject *parent = 0);
    ~Consumer();
protected:
    void run();
private:
    Samples* samples;
};

#endif // CONSUMER_H
