#ifndef OBJECTPROCREATOR_H
#define OBJECTPROCREATOR_H

/*!
 * Базовый класс для всех сущностей, которые необходимо описать в проектном файле.
 */


#include <QJsonObject>

class ObjectProCreator
{
public:
    /*!
     * \brief clear - Метод производит очистку экземпляра класса от всех внесённых изменений.
     * Данная функция бывает полезна, например для того, чтобы сбросить ранее внесённые
     * настройки и повторно использовать экземпляр класса.
     */
    void clear();

    /*!
     * \brief fill - Экземпляры данного класса и экземпляры его потомков рекомендуется
     * использовать в качестве элемента коллекции QJsonArray. Данная функция добавляет
     * текущий экземпляр в коллекцию.
     * \param objArray - В данную коллекцию будет занесены настройки, содержащиеся в текущем
     * экземпляре.
     */
    void fill(QJsonArray& objArray) const;
protected:
    /*!
     * \brief insertProperty - Метод добавляет к настройкам новое поле.
     * \param key - Ключ поля.
     * \param value - Значение поля.
     */
    void insertProperty(const QString& key, const QVariant& value);

    /*!
     * \brief obj - Хранит текущие настройки. Объявлен как mutable, так как изменяется из
     * константной функции fill(...) const.
     */
    mutable QJsonObject obj;
};

#endif // OBJECTPROCREATOR_H
