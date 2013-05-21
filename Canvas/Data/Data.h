#ifndef DATA_H
#define DATA_H

class QXmlStreamWriter;
class QXmlStreamReader;
class Canvas;
class QListWidget;
class DataFromFile;

#include <QObject>
#include <QVector>
#include <QString>

class Data: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Data)
private slots:
    void createSignal(DataFromFile* dataFromFile);
protected:
    explicit Data(QObject* parent = 0);
    static Data* instance;
public slots:
    void cleanFiles();
public:
    static Data* getInstance();
    ~Data();
    void clear();
    void pushBack(QString getPath);
    void stopLoadData();//Terminate all threads.
    void fill(Canvas* canvas);
    void deleteData(int i);
    void replaceData(int i, QWidget* parent);
    QString getPath() const;
//Write/Read to/from xml
    void save(QXmlStreamWriter& out, QString projectName) const;
    void read(QXmlStreamReader& in, QString projectName);
//Load files
    void loadFiles(QWidget* parent);
signals:
    void dataWasLoaded(DataFromFile* data_from_file);
    void dataWasDeleted(int i);
    void dataWasReplaced(int i, DataFromFile* data_from_file);
private:
    QVector<DataFromFile*> data;
    QString path; //Here is saving last directory the files have been loaded from.
    bool isReplaced; int indexReplace; //Its necessary for createSignal to distinguish pushBack and replace.
};

#endif // DATA_H
