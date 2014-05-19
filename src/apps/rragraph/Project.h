#ifndef PROJECT_H
#define PROJECT_H

class QAction;
class QActionGroup;
class Groups;
#include <QThread>
#include <QObject>
/*!
 * \brief The Project class реализует интерфейс, который позволяет пользователю
 *манипулировать с набором настроек для графиков.
 *Проектный файл имеет формат json и повторяет агрегацию классов данного проекта.
 */
class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(Groups* groups, QWidget* parent);
    ~Project();
    /*!
     * \brief load позволяет загружать проект напрямую без всяких посредников.
     *Функция используется, например, при обработке аргументов командной строки.
     * \param path путь к проекту.
     */
    void load(const QString& path);
    const QString& getPathToPro() const;
public slots:
    /*!
     * \brief load загружаем проект из внешнего источника.
     */
    void load();
    /*!
     * \brief load в меню "Проект" главного окна присутствует список последних проектов,
     *с которыми работал пользователь. Данная функция позволяет загрузить один из них.
     * \param action хранит информацию о местоположении проекта.
     */
    void load(QAction* action);
    /*!
     * \brief reload метод делает перезагрузку текущего проекта. Если на данный момент ни
     *одни из проектов не открыт, данная функция становится аналогичной load().
     */
    void reload();
    /*!
     * \brief close закрывает текущий проект: будут закрыты все группы графиков.
     */
    void close();
    /*!
     * \brief save сохраняет проект под текущем именем. Если на данный момент ни
     *одни из проектов не открыт, данная функция аналогична saveAs().
     * \return
     */
    bool save();
    /*!
     * \brief saveAs сохраняет проект под другим именем. Все ссылки на внутрении данные будут
     *обновлены.
     * \return успешность сохранения. Эта информация необходима, чтобы обработать действия пользователя
     *при выходе из программы: отменить выход, сохранить и выйти, выйти без сохранения.
     */
    bool saveAs();
    /*!
     * \brief forKojnevAlexandrNikolayevich данная функция названа в честь одного из тестеров программы, который
     *убедительно доказывал необходимость существования представленного в ней функционала.
     *Функция копирует проектный файл в другое место.
     */
    void forKojnevAlexandrNikolayevich();
    /*!
     * \brief forDeminValeriyNikolayevich ещё одна именная функция, назначение которой сводится к
     *загрузке проектного файла, относящегося к третей серии Rragraph.
     */
    void forDeminValeriyNikolayevich();
signals:
    /*!
     * \brief wasReplaced загружен новый проект.
     * \param path путь к новому проекту.
     */
    void wasReplaced(const QString& path);
    /*!
     * \brief wasClosed проект был закрыт.
     */
    void wasClosed();
    void beginReading();
    void endReading();
private:
    QWidget* parent;
    class ProjectPrivateData;
    ProjectPrivateData* d;
};

#endif // PROJECT_H
