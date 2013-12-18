#ifndef TRANSLATOR_H
#define TRANSLATOR_H

class QActionGroup;
class QMenu;
class QAction;
#include <QObject>
#include "global.h"
#include <QTranslator>
#include <QDir>

class Translator : public QObject
{
    Q_OBJECT
    SINGLETON_HEADER(Translator, QObject)
public:
    ~Translator();
    void fill(QMenu* menu);
    void restore();
signals:
    void localeWasChanged();
private slots:
    void wasChoosen(QAction* language);
private:
    void serialize() const;
    void createNativeLocale();
    void createAvailableLocales();
    void createNewAction(const QString& language, const QString& locale);
    QActionGroup* languages;
    QString nativeLocale;
    QTranslator appTranslator;
    QDir qmsDir;
};

#endif // TRANSLATOR_H
