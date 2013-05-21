#ifndef ITEM_H
#define ITEM_H

class QSettings;
class QModelIndex;
#include <QVariant>
#include <QString>
#include <QList>

class QXmlStreamWriter;
class QXmlStreamReader;

class Item
{
public:
//Item's types
    enum Type{
            ROOT_PLOT,
                PLOT_NAME,
                    PLOT_STYLE,
                        PLOT_STYLE_FONT,
                    PLOT_LEGEND,
                        PLOT_LEGEND_FONT,
                        PLOT_LEGEND_POSITION,
                    PLOT_ABSCISS_AXIS,
                        PLOT_ABSCISS_AXIS_FONT,
                        PLOT_ABSCISS_TITLE_FONT,
                    PLOT_ORDINATE_AXIS,
                        PLOT_ORDINATE_AXIS_FONT,
                        PLOT_ORDINATE_TITLE_FONT,
            ROOT_CURVE,
                CURVE_NAME,
                    CURVE_LINE,
                        CURVE_LINE_DASH,
                        CURVE_LINE_SPACE,
                        CURVE_LINE_WIDTH,
                        CURVE_LINE_COLOR,
                    CURVE_MARKER,
                        CURVE_MARKER_BEGIN_POINT,
                        CURVE_MARKER_STEP,
                        CURVE_MARKER_SIZE,
                        CURVE_MARKER_TYPE,
                        CURVE_MARKER_COLOR,
        CHILD_GROUP
    };
static const QString getCaption(Type getType);
//Constructor and destructor.
    Item(Type getType, const QVariant& value = QVariant(), Item* getParent = 0);
    ~Item();
//Get Item from QModelIndex
    static Item* item(const QModelIndex& index);
//Restore data from register.
    void restore(const QString& group);
    void save(const QString& group);
    void save(QXmlStreamWriter& out);
    void read(QXmlStreamReader& in);
private:
    void readItem(QXmlStreamReader& in);
    void restoreFrom(QSettings& settings);
    void saveToRegister(QSettings& settings);
    void clearRegister(QSettings& settings);
public:
//Access to _children.
    void pushBack(Type getType, const QVariant& value = QVariant());
    void insert(int row, Type getType, const QVariant& value = QVariant());
    void remove(int i);
    Item* getParent();
    Item* child(int i);
    Item* last();
    Item* find(Type getType);
    QVector<Item*> findLineParams();
//Return the data.
    const QVariant& getValue() const;
    Type getType() const;
    const QString getCaption() const;
//Set data's information.
    void setValue(const QVariant& value);
//The _children's properties.
    int childrenCount() const;
    bool isEmpty() const;
    bool isEditable(const QModelIndex& index) const;
    bool isStyleFont() const;
    bool isStyleColor() const;
    bool isStyleName() const;
    bool isStyleRoot() const;
    bool isStyleInt() const;
    //If this class has a _parent, than this class is _parent::_children[child_number()].
    int getChildNumber() const;
private:
    Type type;
    QVariant value;
    Item* parent;
    QList<Item*> children;
};

#endif // ITEM_H
