#ifndef DYNAMICCOLUMN_H
#define DYNAMICCOLUMN_H

#include <QString>
#include <QXmlStreamWriter>
#include <QObject>

struct DynamicColumn{
    QString header;
    float mult;
    QString style;
    bool isOne() const{ return mult == 1; }
    QString getHeader() const{
        return isOne() ? header : QString("%1*(%2)").arg(mult).arg(header);
    }

//Write to xml
    void save(QXmlStreamWriter& out) const{
        out.writeStartElement("column");
            if(!header.isEmpty()) out.writeAttribute("header", header);
            if(mult != 1)         out.writeAttribute("mult",   QString("%1").arg(mult));
            if(!style.isEmpty())  out.writeAttribute("style",  style);
        out.writeEndElement();
    }
//Read from xml
    void read(QXmlStreamReader& in){
        if(in.attributes().hasAttribute("header")) header = in.attributes().value("header").toString();
        if(in.attributes().hasAttribute("mult"))   mult   = in.attributes().value("mult") .toString().toFloat();
        if(in.attributes().hasAttribute("style"))  style  = in.attributes().value("style").toString();
    }

    DynamicColumn(QString header = QString()) : header(header), mult(1){}
};

#endif // DYNAMICCOLUMN_H
