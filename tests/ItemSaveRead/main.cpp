#include <QApplication>
#include <QXmlStreamWriter>
#include <QFile>
#include <QTextCodec>
#include "../../Styles/Item/Item.h"
#include <QFileDialog>
#include <QLabel>
#include <QDebug>

int main(int argc, char** argv){
    QApplication ItemSaveRead(argc, argv);

    QApplication::setOrganizationName("Fakel");
    QApplication::setApplicationName("Rragraph");
    QApplication::setApplicationVersion("3.0");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp1251"));
    QLabel lbl(QObject::tr("True"));


    QFile file(QApplication::applicationDirPath() + "/read.xml");
    file.open(QFile::ReadOnly);
    QXmlStreamReader in(&file);

    QFile file2(QApplication::applicationDirPath() + "/save.xml");
    file2.open(QFile::WriteOnly);
    QXmlStreamWriter out(&file2);


    Item* item = new Item(Item::CHILD_GROUP);
        in.readNext();
        qDebug() << in.name() << " " <<in.tokenType();
        item->read(in);

        out.setAutoFormatting(true);
        out.writeStartDocument();
        item->save(out);
        out.writeEndDocument();
    delete item;

        file.close();
        file2.close();
    lbl.show();

    return ItemSaveRead.exec();
}
