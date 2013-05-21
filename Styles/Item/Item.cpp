#include "Item.h"

#include <QStringList>
#include <QObject>

Item::Item(Type type, const QVariant& value, Item* parent):
    type(type),
    value(value),
    parent(parent)
{    
}

Item::~Item()
{
    qDeleteAll(children);
}

//Get Item from QModelIndex
#include <QModelIndex>
Item* Item::item(const QModelIndex& index)
{
    return static_cast<Item*>(index.internalPointer());
}

//Restore data from register.
#include <QSettings>
#include <QString>
void Item::restore(const QString& group)
{
    QSettings settings;
    settings.beginGroup(group);
        restoreFrom(settings);
    settings.endGroup();
}

void Item::save(const QString &group)
{
    QSettings settings;
    settings.beginGroup(group);
        clearRegister(settings);
        saveToRegister(settings);
    settings.endGroup();
}

#include <QXmlStreamWriter>
#include <QFont>
void Item::save(QXmlStreamWriter& out)
{
    out.writeStartElement("item");
        out.writeAttribute("type", QString("%1").arg(type));
        out.writeAttribute("value", value.toString());
        foreach(Item* child, children){
            child->save(out);
        }
    out.writeEndElement();
}

#include <QXmlStreamReader>

void Item::Item::read(QXmlStreamReader& in)
{    
    qDeleteAll(children);
    children.clear();
    in.readNext();
    readItem(in);
}

void Item::readItem(QXmlStreamReader& in)
{
    if(in.name() == "item" && in.tokenType() == QXmlStreamReader::StartElement){
        type  = (Type) in.attributes().value("type").toString().toInt();
        value = in.attributes().value("value").toString();
        while(!in.atEnd()){
            in.readNext();
            if(in.name() == "item"){
                if(in.tokenType() == QXmlStreamReader::StartElement){
                    pushBack(CHILD_GROUP);
                    last()->readItem(in);
                }else{
                    if(in.tokenType() == QXmlStreamReader::EndElement){
                        return;
                    }
                }
            }
        }
    }
}

void Item::restoreFrom(QSettings& settings)
{
    value = settings.value("value");
    if(settings.contains("type")) type  = (Type) settings.value("type").toInt();
    QStringList children = settings.childGroups();
    foreach(QString key, children){
        pushBack(CHILD_GROUP);
        settings.beginGroup(key);
            last()->restoreFrom(settings);
        settings.endGroup();
    }
}

void Item::saveToRegister(QSettings& settings)
{
    settings.beginGroup(getCaption());
        settings.setValue("type", type);
        settings.setValue("value", value);
        foreach(Item* item, children) item->saveToRegister(settings);
    settings.endGroup();
}

void Item::clearRegister(QSettings& settings)
{
    settings.beginGroup(getCaption());
        foreach(QString key, settings.childGroups() + settings.childKeys()) settings.remove(key);
    settings.endGroup();
}

//Access to _children.
void Item::pushBack(Type type, const QVariant& value)
{
    children.push_back(new Item(type, value, this));
}

void Item::insert(int row, Type type, const QVariant& value)
{
    children.insert(row, new Item(type, value, this));
}

void Item::remove(int i)
{
    delete children.takeAt(i);
}

Item* Item::getParent()
{
    return parent;
}

Item* Item::child(int i)
{
    return i < 0 || i >= children.size() ? 0 : children.at(i);
}

Item* Item::last()
{
    return children.last();
}

Item* Item::find(Type type)
{
    foreach(Item* item, children){
        if(item->getType() == type) return item;
    }
    return 0;
}

QVector<Item*> Item::findLineParams()
{
    QVector<Item*> result(4, 0);
    foreach(Item* item, children){
        if(item->getType() == CURVE_LINE_COLOR){
            result[0] = item;
        }else if(item->getType() == CURVE_LINE_DASH){
            result[1] = item;
        }else if(item->getType() == CURVE_LINE_SPACE){
            result[2] = item;
        }else if(item->getType() == Item::CURVE_LINE_WIDTH){
            result[3] = item;
        }
    }

    return result;
}

//Return the data.
const QVariant& Item::getValue() const
{
    return value;
}

Item::Type Item::getType() const
{
    return type;
}

const QString Item::getCaption() const
{
    if(type == PLOT_NAME || type == CURVE_NAME) return value.isValid() ? value.toString() : getCaption(type);
    return getCaption(type);
}

void Item::setValue(const QVariant& value)
{
    this->value = value;
}

//The _children's count.
int Item::childrenCount() const
{
    return children.count();
}

bool Item::isEmpty() const
{
    return children.isEmpty();
}

bool Item::isEditable(const QModelIndex& index) const
{
    return
        type == CURVE_MARKER ||
        type == PLOT_STYLE   || type == PLOT_ABSCISS_AXIS || type == PLOT_ORDINATE_AXIS ||
        type == CURVE_LINE   || type == PLOT_LEGEND       ||
        isStyleColor()       || isStyleFont()             || isStyleRoot()              ||
        (!index.column() && !isStyleName()) || (index.column() && isStyleName()) ? false : true;
}

bool Item::isStyleColor() const
{
    return type == CURVE_LINE_COLOR || type == CURVE_MARKER_COLOR ? true : false;
}

bool Item::isStyleFont() const
{
    return type == PLOT_STYLE_FONT          || type == PLOT_LEGEND_FONT || type == PLOT_ABSCISS_AXIS_FONT ||
           type == PLOT_ORDINATE_AXIS_FONT  || type == PLOT_ABSCISS_TITLE_FONT ||
           type == PLOT_ORDINATE_TITLE_FONT ? true : false;
}

bool Item::isStyleName() const
{
    return type == PLOT_NAME || type == CURVE_NAME;
}

bool Item::isStyleRoot() const
{
    return type == ROOT_PLOT || type == ROOT_CURVE;
}

bool Item::isStyleInt() const
{
    return type == CURVE_LINE_DASH || type == CURVE_LINE_SPACE || type == CURVE_LINE_WIDTH ||
           type == CURVE_MARKER_BEGIN_POINT || type == CURVE_MARKER_STEP || type == CURVE_MARKER_SIZE;
}

//If this class has a _parent, than this class is parent::children[childNumber()].
int Item::getChildNumber() const
{
    return parent ? parent->children.indexOf(const_cast<Item*>(this)) : 0;
}

const QString Item::getCaption(Type type)
{
    if(type == ROOT_PLOT) return "Root plot";
        if(type == PLOT_NAME) return QObject::tr("New style");
            if(type == PLOT_STYLE) return QObject::tr("Plot style");
                if(type == PLOT_STYLE_FONT) return QObject::tr("Font");
            if(type == PLOT_LEGEND) return QObject::tr("Legend");
                if(type == PLOT_LEGEND_FONT) return QObject::tr("Font");
                if(type == PLOT_LEGEND_POSITION) return QObject::tr("Position");
            if(type == PLOT_ABSCISS_AXIS) return QObject::tr("Absciss");
                if(type == PLOT_ABSCISS_AXIS_FONT)  return QObject::tr("Axis font");
                if(type == PLOT_ABSCISS_TITLE_FONT) return QObject::tr("Title font");
            if(type == PLOT_ORDINATE_AXIS) return QObject::tr("Ordinate");
                if(type == PLOT_ORDINATE_AXIS_FONT)  return QObject::tr("Axis font");
                if(type == PLOT_ORDINATE_TITLE_FONT) return QObject::tr("Title font");
    if(type == ROOT_CURVE) return "Root curve";
        if(type == CURVE_NAME) return QObject::tr("New style");
            if(type == CURVE_LINE) return QObject::tr("Line");
                if(type == CURVE_LINE_DASH)  return QObject::tr("Dash");
                if(type == CURVE_LINE_SPACE) return QObject::tr("Space");
                if(type == CURVE_LINE_WIDTH) return QObject::tr("Width");
                if(type == CURVE_LINE_COLOR) return QObject::tr("Color");
            if(type == CURVE_MARKER) return QObject::tr("Marker");
                if(type == CURVE_MARKER_BEGIN_POINT)  return QObject::tr("Begin point");
                if(type == CURVE_MARKER_STEP)  return QObject::tr("Step");
                if(type == CURVE_MARKER_SIZE)  return QObject::tr("Size");
                if(type == CURVE_MARKER_TYPE)  return QObject::tr("Type");
                if(type == CURVE_MARKER_COLOR) return QObject::tr("Color");
    return QObject::tr("Unknown item");
}
