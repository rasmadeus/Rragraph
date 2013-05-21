#ifndef READERFILE_H
#define READERFILE_H

class DataFromFile;
#include <QThread>

class ReaderFile : public QThread
{
    Q_OBJECT
public:
    explicit ReaderFile(DataFromFile* dataFromFile, QObject *parent = 0);
protected:
    void run();
private:
    DataFromFile* dataFromFile;
signals:
    void dataWasLoaded(DataFromFile* dataFromFile);
    void deleteMePlease();
};

#endif // READERFILE_H
