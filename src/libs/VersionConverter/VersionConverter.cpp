#include "VersionConverter.h"

#include <QXmlStreamReader>
#include <QJsonObject>
void parseTileType(QJsonObject& group, QXmlStreamReader& proThirdVerReader)
{
    group.insert("tileType", proThirdVerReader.readElementText().toInt());
}

#include <QString>
void parseReportSize(QJsonObject& plot, QXmlStreamReader& proThirdVerReader)
{
    if(proThirdVerReader.tokenType() == QXmlStreamReader::StartElement){
        const QXmlStreamAttributes attr = proThirdVerReader.attributes();
        if(attr.size() == 2){
            plot.insert("exportSize", attr.first().value().toString() + " " + attr.last().value().toString());
        }
    }
}

void parseAxisType(const QString& axisType, QJsonObject& plot, QXmlStreamReader& proThirdVerReader)
{
    if(proThirdVerReader.tokenType() == QXmlStreamReader::StartElement){
        if(proThirdVerReader.name() == "caption"){
            plot.insert(axisType + "Title", proThirdVerReader.readElementText());
        }
        else
        if(proThirdVerReader.name() == "min"){
           plot.insert(axisType + "Min", proThirdVerReader.readElementText().toDouble());
        }
        else
        if(proThirdVerReader.name() == "max"){
           plot.insert(axisType + "Max", proThirdVerReader.readElementText().toDouble());
        }
        else
        if(proThirdVerReader.name() == "step"){
           plot.insert(axisType + "Step", proThirdVerReader.readElementText().toDouble());
        }
    }
}

void parseAxis(QJsonObject& plot, QXmlStreamReader& proThirdVerReader)
{
    const QXmlStreamAttributes attr = proThirdVerReader.attributes();
    const QString attrFirstName = attr.isEmpty() ? "absciss" : attr.first().value().toString();
    while(!proThirdVerReader.atEnd()){
        proThirdVerReader.readNext();
        if(proThirdVerReader.name() == "axis"){
            break;
        }
        parseAxisType(attrFirstName == "absciss" ? "x" : "y", plot, proThirdVerReader);
    }
}

#include <QSet>
#include <QJsonArray>
struct CurvesIndex
{
    CurvesIndex():
        x(0)
    {
    }

    int x;
    QSet<int> ys;
};

void parseIndex(CurvesIndex& indexes, QXmlStreamReader& proThirdVerReader)
{
    const QXmlStreamAttributes attr = proThirdVerReader.attributes();
    if(attr.value("type").toString() == "absciss"){
        indexes.x = attr.value("value").toInt();
    }
    else{
        indexes.ys.insert(attr.value("value").toInt());
    }
}

#include <QSettings>
void restoreLine(const QSettings& s, QJsonObject& curveSettings)
{
    curveSettings.insert("penColor", s.value("Color/value", "#000").toString());
    curveSettings.insert("penWidth", s.value("Width/value", "1").toString());
    {
        const QString dash = s.value("Dash/value").toString();
        const QString space = s.value("Space/value").toString();
        if(dash.size() || space.size()){
            curveSettings.insert("dashPattern", dash + " " + space);
        }
    }
}

void restoreSymbol(const QSettings& s, QJsonObject& curveSettings)
{
    curveSettings.insert("step", s.value("Step/value", "1").toString());
    curveSettings.insert("symbolStyle", s.value("Type", "-1").toString());
}

void tryRestoreStyleFrom(const QString& styleName, QJsonObject& curveSettings)
{
    QSettings s("Fakel", "Rragraph");
    s.beginGroup("Styles");
        s.beginGroup("Root curve");
            s.beginGroup(styleName);
                s.beginGroup("Line");
                    restoreLine(s, curveSettings);
                s.endGroup();
                s.beginGroup("Marker");
                    restoreSymbol(s, curveSettings);
                s.endGroup();
            s.endGroup();
        s.endGroup();
    s.endGroup();
}

void parseColumn(QJsonArray& curvesSettings, QXmlStreamReader& proThirdVerReader)
{
    QJsonObject curveSettings;
    const QXmlStreamAttributes attr = proThirdVerReader.attributes();
    tryRestoreStyleFrom(attr.value("style").toString(), curveSettings);
    curvesSettings.append(curveSettings);
}

void copyProperty(QJsonObject& dst, const QJsonObject& src, const QString& key)
{
    if(src.contains(key)){
        dst.insert(key, src.value(key));
    }
}

void restoreCurveSettings(QJsonObject& curve, int y, const QJsonArray& curvesSettings)
{
    QJsonObject settings;
    if(y < curvesSettings.size()){
         settings = curvesSettings[y].toObject();
    }
    curve.insert(QString("%1").arg(y), settings);
}

void createCurves(QJsonObject& curve, const CurvesIndex& indexes, const QJsonArray& curvesSettings)
{
    curve.insert("x", indexes.x);
    foreach(int y, indexes.ys){
        restoreCurveSettings(curve, y, curvesSettings);
    }
}

void parseCurve(QJsonArray& curves, QXmlStreamReader& proThirdVerReader)
{
    QJsonObject curve;
    QJsonArray curvesSettings;
    CurvesIndex indexes;
    while(!proThirdVerReader.atEnd()){
        proThirdVerReader.readNext();
        if(proThirdVerReader.name() == "file"){
            break;
        }
        if(proThirdVerReader.tokenType() == QXmlStreamReader::StartElement){
            if(proThirdVerReader.name() == "column"){
                parseColumn(curvesSettings, proThirdVerReader);
            }
            else
            if(proThirdVerReader.name() == "index"){
                parseIndex(indexes, proThirdVerReader);
            }
        }
    }
    createCurves(curve, indexes, curvesSettings);
    curves.append(curve);
}

void parseCaption(QJsonObject& plot, QXmlStreamReader& proThirdVerReader)
{
    plot.insert("title", proThirdVerReader.readElementText());
}

void parsePlot(QJsonArray& plots, QXmlStreamReader& proThirdVerReader)
{
    QJsonObject plot;
    QJsonArray curves;
    while(!proThirdVerReader.atEnd()){
        proThirdVerReader.readNext();
        if(proThirdVerReader.name() == "plot"){
            break;
        }
        if(proThirdVerReader.tokenType() == QXmlStreamReader::StartElement){
            if(proThirdVerReader.name() == "report"){
                parseReportSize(plot, proThirdVerReader);
            }
            else
            if(proThirdVerReader.name() == "axis"){
                parseAxis(plot, proThirdVerReader);
            }
            else
            if(proThirdVerReader.name() == "file"){
               parseCurve(curves, proThirdVerReader);
            }
            else
            if(proThirdVerReader.name() == "caption"){
               parseCaption(plot, proThirdVerReader);
            }
        }
    }
    if(!curves.isEmpty()) plot.insert("Curves", curves);
    plots.append(plot);
}

void parseData(QJsonArray& samples, QXmlStreamReader& proThirdVerReader)
{
    if(proThirdVerReader.tokenType() == QXmlStreamReader::StartElement){
        QJsonObject sample;
        if(proThirdVerReader.attributes().size() && proThirdVerReader.attributes().first().name() == "path"){
            sample.insert("path", proThirdVerReader.attributes().value("path").toString());
        }
        samples.append(sample);
    }
}

void parseGroup(QJsonArray& groups, QXmlStreamReader& proThirdVerReader)
{
    QJsonObject group;
    QJsonArray plots;
    QJsonArray samples;
    while(!proThirdVerReader.atEnd()){
        proThirdVerReader.readNext();
        if(proThirdVerReader.name() == "Project"){
            break;
        }
        if(proThirdVerReader.tokenType() == QXmlStreamReader::StartElement){
            if(proThirdVerReader.name() == "tileType"){
               parseTileType(group, proThirdVerReader);
            }
            else
            if(proThirdVerReader.name() == "plot"){
               parsePlot(plots, proThirdVerReader);
            }
            else
            if(proThirdVerReader.name() == "file"){
               parseData(samples, proThirdVerReader);
            }
        }
    }
    if(!group.isEmpty()) group.insert("group", plots);
    if(!samples.isEmpty()) group.insert("Samples", samples);
    groups.append(group);
}

#include <QFile>
void fillRoot(QJsonObject& root, const QString& pathToThirdVer)
{
    QFile proThirdVer(pathToThirdVer);
    if(proThirdVer.open(QFile::ReadOnly)){
        QXmlStreamReader proThirdVerReader(&proThirdVer);
        QJsonArray groups;
            while(proThirdVerReader.readNextStartElement()){
                if (proThirdVerReader.name() == "Project"){
                    parseGroup(groups, proThirdVerReader);
                }
            }
        if(!groups.isEmpty()){
            root.insert("groups", groups);
        }
    }
}

#include <QJsonDocument>
#include <QVariant>
QJsonDocument jumpFromThirdToFourth(const QString& pathToThirdVer)
{
    QJsonDocument doc;
        QJsonObject root;
            fillRoot(root, pathToThirdVer);
        root.insert("rragraphVersion", QJsonValue::fromVariant("4.2.0"));
    doc.setObject(root);
    return doc;
}
