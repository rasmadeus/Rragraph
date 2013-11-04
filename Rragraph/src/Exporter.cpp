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
     const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
     QStringList filter;
    #ifndef QT_NO_PRINTER
        filter += QString("PDF ") + tr("Documents") + " (*.pdf)";
    #endif
    #ifndef QWT_NO_SVG
        filter += QString("SVG ") + tr("Documents") + " (*.svg)";
    #endif
    #ifndef QT_NO_PRINTER
        filter += QString("Postscript ") + tr("Documents") + " (*.ps)";
    #endif

     if(imageFormats.size() > 0){
         QString imageFilter(tr("Images"));
         imageFilter += " (";
         for(int i = 0; i < imageFormats.size(); i++){
             if(i > 0){
                 imageFilter += " ";
             }
             imageFilter += "*.";
             imageFilter += imageFormats[i];
         }
         imageFilter += ")";
         filter += imageFilter;
    }

    const QString fileName = QFileDialog::getSaveFileName(
        src,
        tr("Export File Name"),
        exportPath(),
        filter.join(";;"),
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
