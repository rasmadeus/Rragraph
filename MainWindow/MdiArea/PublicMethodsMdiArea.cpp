#include "MdiArea.h"

MdiArea::MdiArea(QMdiArea* area, QObject *parent) :
    QObject(parent),
    area(area)
{
}

int MdiArea::getTileType() const
{
    return tileType;
}

#include <QFileDialog>
#include <QMdiArea>
#include "../../Canvas/Canvas.h"
#include <QMdiSubWindow>
void MdiArea::toPngImages(const QString& dir)
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList()){
        QImage image = Canvas::image(static_cast<Canvas*>(subWindow->widget()));
        image.save(dir + "/" + subWindow->windowTitle()+".png");
    }
}

#include <QPrinter>
#include <QPainter>
#include "../../qwt-6.0.1/qwt_plot_renderer.h"
void MdiArea::toPdf(const QString& path)
{
    QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setPageMargins(20, 30, 20, 10, QPrinter::Millimeter);
        printer.setOrientation(QPrinter::Landscape);
        printer.setOutputFileName(path);

    QwtPlotRenderer pr(this);
        pr.setLayoutFlag(QwtPlotRenderer::FrameWithScales);

    QRectF rect( 0, 0, printer.width(), printer.height());
    double aspect = rect.width() / rect.height();
    if (( aspect < 1.0)){
        rect.setHeight( aspect * rect.width() );
    }

    QPainter p(&printer);
    for(int i=0; i<area->subWindowList().size(); ++i){
        if(i) printer.newPage();
        QwtPlot* plot = static_cast<QwtPlot*>(area->subWindowList()[i]->widget());
        pr.render(plot, &p, rect);
    }
}

#include <QXmlStreamWriter>
void MdiArea::save(QXmlStreamWriter &out, const QString& projectName)
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList()){
        static_cast<Canvas*>(subWindow->widget())->save(out, projectName);
    }
}

void MdiArea::readLast(QXmlStreamReader &in)
{
    static_cast<Canvas*>(area->subWindowList().last()->widget())->read(in);
}

void MdiArea::retranslate()
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList())
    {
        setTitle(subWindow);
        static_cast<Canvas*>(subWindow->widget())->retranslate();
    }
}
