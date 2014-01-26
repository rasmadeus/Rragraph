#ifndef RRAGRAPHPROCREATOR_H
#define RRAGRAPHPROCREATOR_H

/*!
 * Предоставляемый интефейс предназначен для формирования
 * проектного файла программы Rragraph версии 4.1.
 */

class GroupProCreator;
#include <QJsonArray>
#include <QString>

class RragraphProCreator
{

public:
    /*!
     * \brief read - Метод предназначен для чтения проектного файла программы Rragraph с
     *        жёсткого диска или другого носителя.
     *        Все внесённые изменения в объект до вызова этого метода будут потеряны.
     * \param pathToPro - Путь к проектному файлу.
     * \return  - Успешность чтения проектного файла.
     */
    bool read(const QString& pathToPro);

    /*!
     * \brief save - Метод предназначен для сохранения проектного файла
     *        программы Rragraph на жёсткий диск или на иной носитель.
     * \param pathToPro - По данному пути будет сохранён проектный файл.
     * \return - Возвращает успешность сохранения проектного файла.
     */
    bool save(const QString& pathToPro) const;

    /*!
     * \brief clear - Данный метод очищает объект от всех ранее внесённых изменений.
     */
    void clear();

    /*!
     * \brief appendGroup - Метод создаёт новую группу графиков.
     */
    void appendGroup(GroupProCreator& group);
protected:
    /*!
     * \brief groups - Содержит описание  групп графиков.
     */
    QJsonArray groups;
};

#endif // RRAGRAPHPROCREATOR_H
