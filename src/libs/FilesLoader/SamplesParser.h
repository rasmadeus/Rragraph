#ifndef SAMPLESPARSER_H
#define SAMPLESPARSER_H

class SamplesPrivateData;
#include <QThread>

class SamplesParser : public QThread
{
    Q_OBJECT
public:
    explicit SamplesParser(SamplesPrivateData* samples, QObject* parent = 0);
private:
    SamplesPrivateData* samples;
};

#endif // SAMPLESPARSER_H
