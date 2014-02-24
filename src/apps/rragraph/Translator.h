#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QTranslator>
class QMenu;
class QActionGroup;
class QAction;
#include <QDir>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QMenu* languagesMenu, QObject* parent = 0);
    ~Translator();
    void tryRestoreLocale();
signals:
    void localeWasChanged();
private slots:
    void appLocaleWasChanged(QAction* action);
private:
    void fill(QMenu* languagesMenu);
    void createEnglishLocale();
    void createAvailaibleLocales();
    void createLocale(const QString& language, const QString& locale);
    void initLocalesActions();
    void installTranslators();
    QString locale(QAction* action) const;
    QDir tsDir;
    QActionGroup* languages;
    QTranslator appTs;
    QTranslator libsAppTs;
    QTranslator qtTs;
};

#endif // TRANSLATOR_H
