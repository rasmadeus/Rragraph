#include "Translator.h"

#include <QApplication>
Translator::Translator(QObject *parent) :
    QObject(parent)
{
    qmPath = qApp->applicationDirPath() + "/translations";
    qApp->installTranslator(&appTranslator);
}

#include <QDir>
#include <QActionGroup>

void Translator::createActionGroup(QActionGroup *group)
{
    connect(group, SIGNAL(triggered(QAction*)), this, SLOT(switchLanguage(QAction*)));
    QAction* action = new QAction(tr("&%1 %2").arg(1).arg("English"), this);
    action->setCheckable(true);
    action->setChecked(true);
    group->addAction(action);

    QDir dir(qmPath);
    QStringList translations_paths = dir.entryList(QStringList("translation_*.qm"));
    for(int i=0; i<translations_paths.size(); ++i){
        QString locale = translations_paths[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.truncate(locale.lastIndexOf('.'));

        QTranslator translator;
        translator.load(translations_paths[i], qmPath);

        QString language = translator.translate("MainWindow", "English");

        QAction* action = new QAction(tr("&%1 %2").arg(i+2).arg(language), this);
        action->setCheckable(true);
        action->setData(locale);

        group->addAction(action);
    }
}

void Translator::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();
    appTranslator.load("translation_" + locale, qmPath);
    emit retranslate();
}
