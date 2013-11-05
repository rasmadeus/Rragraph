#include "Translator.h"

SINGLETON_IMPLEMENTATION(Translator, QObject)

#include <QApplication>
Translator::Translator(QObject* parent) :
    QObject(parent),
    nativeLocale("English"),
    qmsDir(QApplication::applicationDirPath() + "/translations")
{
    QApplication::installTranslator(&appTranslator);
    languages = new QActionGroup(this);
    connect(languages, SIGNAL(triggered(QAction*)), SLOT(wasChoosen(QAction*)));
}

Translator::~Translator(){
    serialize();
}

void Translator::wasChoosen(QAction* language)
{
    QString locale = language->data().toString();
    appTranslator.load(locale, qmsDir.absolutePath());
    emit localeWasChanged();
}

void Translator::createNativeLocale()
{
    createNewAction(nativeLocale, "en.qm");
    languages->actions().first()->setChecked(true);
}

#include <QDir>
#include <QTranslator>
void Translator::createAvailableLocales()
{
    QStringList locales = qmsDir.entryList(QStringList("*.qm"));
    foreach(const QString& locale, locales){
        QTranslator translator;
        translator.load(locale, qmsDir.absolutePath());
        QString language = translator.translate("Translator", "English");
        createNewAction(language, locale);
    }
}

#include <QMenu>
void Translator::fill(QMenu* menu)
{
    createNativeLocale();
    createAvailableLocales();
    menu->addActions(languages->actions());
}

void Translator::createNewAction(const QString& language, const QString& locale)
{
    QAction* action = new QAction(language, languages);
    action->setCheckable(true);
    action->setData(locale);
    languages->addAction(action);
}

#include <QSettings>
#include <QDebug>
void Translator::serialize() const
{
    QSettings s;
    const QString locale = languages->checkedAction()->data().toString();
    s.setValue("Translator/locale", locale);
}

void Translator::restore()
{
    QSettings s;
    const QString needLocale = s.value("Translator/locale", "en.qm").toString();
    foreach (QAction* language, languages->actions()){
        const QString currentLocale = language->data().toString();
        if(currentLocale == needLocale){
            language->setChecked(true);
            wasChoosen(language);
            return;
        }
    }
}
