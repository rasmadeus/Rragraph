#ifndef CURVEPROCREATOR_H
#define CURVEPROCREATOR_H

/*!
 * Класс предоставляет интерфейс для описания настроек кривой.
 */

#include "ObjectProCreator.h"

class CurveProCreator: public ObjectProCreator
{
public:
    /*!
     * \brief setColor - Здесь задаётся цвет кривой.
     * \code
     * CurveProCreator curve;
     * curve.setColor("#ff0000")
     * \endcode
     */
    void setColor(const QString& color);

    /*!
     * \brief setWidth - Здесь задаётся ширина линии.
     */
    void setWidth(int width);

    /*!
     * \brief setDashPattern - Здесь задаётся штрих-пунктирная линия для кривой. Например если вы зададите строку
     * "3 5 7 5", кривая будет рисоваться следующим образом: штрих - 3 px, пробел - 5 px, штрих - 7 px, пробел - 5 px.
     * \param dashPattern
     */
    void setDashPattern(const QString& dashPattern);

    /*!
     * \brief setSymbolStyle - Установить фигуру, которая будет нарисована на точках кривой.
     * \param style - Указывает вид фигуры. Какая цифра какой фигуре соответствует смотрите в
     * документации к библиотеке Qwt.
     */
    void setSymbolStyle(int style);

    /*!
     * \brief setAddendX - Позволяет задать смещение кривой по оси X.
     */
    void setAddendX(double addend);

    /*!
     * \brief setAddendY - Позволяет задать смещение кривой по оси Y.
     */
    void setAddendY(double addend);

    /*!
     * \brief setMultY - Позволяет масштабировать кривую по оси Y.
     */
    void setMultY(double addend);

    /*!
     * \brief Если кривая содержит много точек на количество пикселей и вы хотите
     * раставить маркеры на кривой - setSymbolStyle(style != -1) - тогда
     * символы будут наезжать друг на друга. Чтобы этого избежать, задайте шаг для точек,
     * на которых вы хотите рисовать символ.
     */
    void setStep(int step);

    /*!
     * \brief setY - Кривая имеет привязку к данным, загруженным из какого-то файла. Данный метод
     * метод задаёт индекс столбца, который является Y - составляющей кривой. X - составляющая и сам
     * файл задаётся в более высокой структуре.
     */
    void setY(int iY);
};

#endif // CURVEPROCREATOR_H
