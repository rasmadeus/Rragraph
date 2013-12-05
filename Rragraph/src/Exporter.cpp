#include "Exporter.h"

Exporter::Exporter():
    exportPath("Exporter/exportPath")
{
}

#include "Plot.h"
#include <QFileDialog>
#include <QImageWriter>
void Exporter::exportOne(Plot* src)
{
    const QString fileName = QFileDialog::getSaveFileName(
        src,
        tr("Export File Name"),
        exportPath(),
        QString("Images(*.png)"),
        nullptr,
        QFileDialog::DontConfirmOverwrite
    );
    if(!fileName.isEmpty()){
        exportPath = fileName;
        renderDocument(src, fileName, src->getExportSize());
    }
}

#include <QPrinter>
#include <QPrintDialog>
void Exporter::printOne(Plot* src)
{
    QPrinter printer(QPrinter::HighResolution);   
    printer.setPaperSize(QPrinter::A4);
    printer.setDocName("Plot");
    printer.setCreator("Rragraph 4.0");
    printer.setOrientation(QPrinter::Landscape);

    QPrintDialog dialog(&printer, src);
    if(dialog.exec()){
        if(printer.colorMode() == QPrinter::GrayScale){
            setDiscardFlag(QwtPlotRenderer::DiscardBackground);
            setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground);
            setDiscardFlag(QwtPlotRenderer::DiscardCanvasFrame);
            setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        }
        renderTo(src, printer);
    }
}

void Exporter::setExportPath(const QString& path){
    exportPath = path;
}

QString Exporter::getExportPath(){
    return exportPath();
}
