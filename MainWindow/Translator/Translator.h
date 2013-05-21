#ifndef TRANSLATOR_H
#define TRANSLATOR_H

class QActionGroup;
class QAction;

#include <QObject>
#include <QTranslator>
#include <QString>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QObject *parent = 0);
    void createActionGroup(QActionGroup* group);
signals:
    void retranslate();
public slots:
    void switchLanguage(QAction* action);
private:
    QString qmPath;
    QTranslator appTranslator;
};

#endif // TRANSLATOR_H
