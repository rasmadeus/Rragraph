#include "Translator.h"

#include <QApplication>
Translator::Translator(QMenu* languagesMenu, QObject* parent) :
    QObject(parent),
    tsDir(QApplication::applicationDirPath() + "/translations")
{
    initLocalesActions();
    createEnglishLocale();
    createAvailaibleLocales();
    fill(languagesMenu);
    installTranslators();
}

#include <QActionGroup>
#include <QSettings>
Translator::~Translator()
{
    QAction* checked = languages->checkedAction();
    QSettings("appSettings.ini", QSettings::IniFormat).setValue("locale", locale(checked));
}

void Translator::tryRestoreLocale()
{
    const QString locale = QSettings("appSettings.ini", QSettings::IniFormat).value("locale").toString();
    foreach(QAction* language, languages->actions()){
        if(locale == this->locale(language)){
            language->setChecked(true);
            appLocaleWasChanged(language);
            break;
        }
    }
}

void Translator::installTranslators()
{
    QApplication::installTranslator(&appTs);
    QApplication::installTranslator(&libsAppTs);
    QApplication::installTranslator(&qtTs);
}

void Translator::initLocalesActions()
{
    languages = new QActionGroup(this);
    connect(languages, SIGNAL(triggered(QAction*)), SLOT(appLocaleWasChanged(QAction*)));
}

#include <QMenu>
void Translator::fill(QMenu* languagesMenu)
{
    languagesMenu->addActions(languages->actions());
}

void Translator::createEnglishLocale()
{
    createLocale("English", "");
}

#include <QTranslator>
void Translator::createAvailaibleLocales()
{
    QStringList locales = tsDir.entryList(QStringList("app_*.qm"));
    foreach(const QString& locale, locales){
        QTranslator translator;
        translator.load(locale, tsDir.absolutePath());
        QString language = translator.translate("LanguagesMenu", "English");
        createLocale(language, locale);
    }
}

#include <QAction>
void Translator::createLocale(const QString& language, const QString& locale)
{
    QAction* action = new QAction(language, languages);
    action->setCheckable(true);
    action->setData(locale);
    languages->addAction(action);
}

void Translator::appLocaleWasChanged(QAction* action)
{
    QString locale = this->locale(action);
    appTs.load(locale, tsDir.absolutePath());
    libsAppTs.load("libs_" + locale, tsDir.absolutePath());
    qtTs.load("qt_" + locale, tsDir.absolutePath());
    emit localeWasChanged();
}

QString Translator::locale(QAction* action) const
{
    return action->data().toString();
}
