#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QMdiSubWindow;
class StylesEditor;
class QProgressBar;
class QXmlStreamWriter;
class QXmlStreamReader;
class QSettings;
class QActionGroup;
class MdiArea;
class RecentlyClosed;

#include "Translator/Translator.h"
#include <QMainWindow>
#include <QTranslator>
#include "Guide/Guide.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadProject(const QString& path);
    void loadFiles(const QStringList& paths);
    static QString getPathToProject();
protected:
    void closeEvent(QCloseEvent* evt);
    void resizeEvent(QResizeEvent* evt);
private slots:
    void callGuide();
    void dataWasShowed();
    void retranslate();
    void readProjectFrom(QString path);
    void toPngImages();
    void toPdf();
    void about();
    void cleanProject();
//Interface's options.
    void setBigButton(bool is);
//Data's slots
    void loadFiles();
//Project's slots
    bool saveAs();
    bool save();
    void read();
    void reopen();    
//Change the application's language
    void setLocale(QString locale);
private:
    bool saveToProjectName();
    void save(QXmlStreamWriter& out);
    void readFromProjectName();
    void read(QXmlStreamReader& in);
    void createArea();
    void createSlotsConnections();
    void saveSettings() const;
    void restoreSettings();
    void createLanguageMenu();
    void createTileBehaviorMenu();
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);
    void setTiler(int type);
private:
    static QString projectName;
    Ui::MainWindow* ui;
    StylesEditor* styleEditor;
    QString reportPngDir, reportPdfDir;

    QActionGroup* languages;
    QActionGroup* tilers;

    Guide guide;
    MdiArea* area;
    Translator translator;
    RecentlyClosed* recentlyClosed;
};

#endif // MAINWINDOW_H
