#ifndef SAMPLESLOADER_H
#define SAMPLESLOADER_H

struct SamplesData;
#include <QThread>

class SamplesLoader : public QThread
{
    Q_OBJECT
public:
    explicit SamplesLoader(SamplesData* samplesData, QObject* parent = 0);
    ~SamplesLoader();
    bool stop();
protected:
    SamplesData* samplesData;
private:
    void stopCrane;
};

#endif // SAMPLESLOADER_H
