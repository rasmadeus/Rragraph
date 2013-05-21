#include "Data.h"
#include "DataFromFile.h"

#include <QSettings>
Data::Data(QObject* parent): QObject(parent), isReplaced(false), indexReplace(0)
{
    QSettings settings;
    path = settings.value("Widget settings/Data/path").toString();
}

Data* Data::instance = 0;

Data* Data::getInstance()
{
    if(!instance) instance = new Data();
    return instance;
}

Data::~Data()
{
    QSettings settings;
    settings.setValue("Widget settings/Data/path", path);
    clear();
    instance = 0;
}
void Data::clear()
{
    stopLoadData();
    foreach(DataFromFile* dataFromFile, data) delete dataFromFile;
    data.clear();
}


void Data::pushBack(QString path)
{
    DataFromFile* dataFromFile = new DataFromFile();
    connect(dataFromFile, SIGNAL(dataWasLoaded(DataFromFile*)),  this, SLOT(createSignal   (DataFromFile*)));
    dataFromFile->loadData(path);
}

#include <QStringList>
#include <QFileDialog>
void Data::loadFiles(QWidget *parent)
{
    QStringList paths = QFileDialog::getOpenFileNames(parent, tr("Select the files..."), path, tr("Text files (*.txt);;Any files (*)"));
    if(!paths.size()) return;
    path = paths[0]; //Saving the files' dir.
    foreach(QString path, paths) pushBack(path);
}

void Data::stopLoadData()
{
    foreach(DataFromFile* dataFromFile, data) dataFromFile->stopLoadData();
}

#include "../Canvas.h"
void Data::fill(Canvas *canvas)
{
    foreach(DataFromFile* dataFromFile, data) canvas->dataWasLoaded(dataFromFile);
}

#include <QXmlStreamWriter>
#include "FilePathParsing/FilePathParsing.h"
void Data::save(QXmlStreamWriter &out, QString projectName) const
{
    out.writeStartElement("Data");
        foreach(DataFromFile* dataFromFile, data){
            out.writeStartElement("file");                
                out.writeAttribute("path", FilePathParsing::getRelativePath(projectName, dataFromFile->getPathToFile()));
            out.writeEndElement();
        }
    out.writeEndElement();
}

#include <QFileInfo>
void Data::read(QXmlStreamReader &in, QString projectName)
{
    while(!in.atEnd()){
        in.readNext();
        if(in.name() == "Data") break;
        if(in.tokenType() == QXmlStreamReader::StartElement){
            if(in.name() == "file") {
                QString path = FilePathParsing::getAbsolutePath(in.attributes().value("path").toString(), projectName);
                pushBack(path);
            }
        }
    }
}

void Data::createSignal(DataFromFile* dataFromFile)
{
    if(isReplaced){ //We want replace data - we do not want data push back.
        isReplaced = false;
        emit dataWasReplaced(indexReplace, dataFromFile);
        return;
    }
    data.push_back(dataFromFile);
    emit dataWasLoaded(dataFromFile);
}

void Data::deleteData(int i)
{
    delete data[i];
    data.remove(i);
    emit dataWasDeleted(i);
}

void Data::cleanFiles()
{
    while(data.size()) deleteData(0);
}

void Data::replaceData(int i, QWidget *parent)
{
    QString path = QFileDialog::getOpenFileName(parent, tr("Choose a file for replacing..."), path);
    if(path.isEmpty()) return;
    path = path;
    isReplaced = true;
    indexReplace = i;
    data[i]->loadData(path);
}

QString Data::getPath() const
{
    return path;
}
