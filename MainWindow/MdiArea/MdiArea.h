#ifndef MDIAREA_H
#define MDIAREA_H

class QXmlStreamWriter;
class QXmlStreamReader;
class QMdiArea;
class QMdiSubWindow;
class QActionGroup;
class QAction;
class QMenu;

#include <QObject>

class MdiArea : public QObject
{
    Q_OBJECT
public:
    explicit MdiArea(QMdiArea* area, QObject *parent = 0);

    enum TileType
    {
       NORMAL,
       HORIZONTAL
    };
//PublicMethodsMdiArea.cpp
    int  getTileType() const;
    void toPngImages(const QString& dir);
    void toPdf(const QString& path);
    void save(QXmlStreamWriter& out, const QString& projectName);
    void readLast(QXmlStreamReader& in);
    void retranslate();
//SlotsMdiArea.cpp
public slots:
    void addWindow();
    void autoscale();
    void replot();
    void reloadStyle();
    void maximizeCurrentWindow();
    void addOneWindow();
    void setTileType(QAction* action);
    void tile();
    void closeAllSubWindows();
private slots:
    void windowWasClosed();
//AuxiliaryMethodsMdiArea.cpp
private:
    void setTitle();
    void setTitle(QMdiSubWindow* subWindow);
    bool isFewWindows();
    void scrollToBegin();
    void scrollToEnd();
//TileMethodsMdiArea.cpp
private:
    void horizontalTile();
    void stackedTile();
signals:
    void showEditor(QWidget*);
private:
    QMdiArea* area;
    TileType tileType;
};

#endif // MDIAREA_H
