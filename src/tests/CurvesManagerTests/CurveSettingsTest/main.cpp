#include <QApplication>
#include <CurveSettings.h>
#include <Curve.h>
int main(int argc, char *argv[])
{
    QApplication CurveSettingsTest(argc, argv);
        Curve curve("TestCurve0");
        QPen pen = curve.pen();
        pen.setWidth(10);
        pen.setColor(QColor("red"));
        curve.setPen(pen);
        CurveSettings curveSettings;
        curveSettings.show();
        curveSettings.setCurve(&curve);
    return CurveSettingsTest.exec();
}
