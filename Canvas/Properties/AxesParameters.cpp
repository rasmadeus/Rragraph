#include "AxesParameters.h"
#include "ui_AxesParameters.h"

QList<AxesParameters*> AxesParameters::objects;

AxesParameters::AxesParameters(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::AxesParameters)
{
    ui->setupUi(this);

    connect(ui->lineEdit_1, SIGNAL(textChanged(QString)), this, SIGNAL(plotTitleChanged(QString)));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SIGNAL(abscissTitleChanged(QString)));
    connect(ui->lineEdit_3, SIGNAL(textChanged(QString)), this, SIGNAL(ordinateTitleChanged(QString)));

    connect(ui->doubleSpinBox_4, SIGNAL(valueChanged(double)), this, SIGNAL(abscissMinChanged(double)));
    connect(ui->doubleSpinBox_5, SIGNAL(valueChanged(double)), this, SIGNAL(abscissMaxChanged(double)));
    connect(ui->doubleSpinBox_6, SIGNAL(valueChanged(double)), this, SIGNAL(abscissStepChanged(double)));
    connect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)), this, SIGNAL(ordinateMinChanged(double)));
    connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)), this, SIGNAL(ordinateMaxChanged(double)));
    connect(ui->doubleSpinBox,   SIGNAL(valueChanged(double)), this, SIGNAL(ordinateStepChanged(double)));

    connect(ui->toolButton_png,   SIGNAL(clicked()), this, SIGNAL(toPngImage()));
    connect(ui->toolButton_PrevStyle, SIGNAL(clicked()), this, SIGNAL(previousStyle()));
    connect(ui->toolButton_NextStyle, SIGNAL(clicked()), this, SIGNAL(nextStyle()));

    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SIGNAL(isAutoscale(bool)));

    objects.push_back(this);

    ui->toolButton->   installEventFilter(this);
    ui->toolButton_1-> installEventFilter(this);
    ui->toolButton_2-> installEventFilter(this);
    ui->toolButton_3-> installEventFilter(this);
    ui->toolButton_5-> installEventFilter(this);
    ui->toolButton_6-> installEventFilter(this);
    ui->toolButton_7-> installEventFilter(this);
    ui->toolButton_8-> installEventFilter(this);
    ui->toolButton_9-> installEventFilter(this);
    ui->toolButton_10->installEventFilter(this);
    ui->toolButton_13->installEventFilter(this);
    ui->toolButton_14->installEventFilter(this);
    ui->toolButton_16->installEventFilter(this);
}

AxesParameters::~AxesParameters()
{
    objects.removeOne(this);
    delete ui;
}

void AxesParameters::retranslate()
{
    ui->retranslateUi(this);
}

void AxesParameters::setAxesInterval(double xm, double xM, double xs, double ym, double yM, double ys)
{
    ui->doubleSpinBox_4->setValue(xm);
    ui->doubleSpinBox_5->setValue(xM);
    ui->doubleSpinBox_6->setValue(xs);
    ui->doubleSpinBox_3->setValue(ym);
    ui->doubleSpinBox_2->setValue(yM);
    ui->doubleSpinBox->  setValue(ys);
}

//Write to XML
#include <QXmlStreamWriter>
void AxesParameters::save(QXmlStreamWriter& out) const
{
    out.writeStartElement("AxesParameters");
    out.writeAttribute("is_autoscale", QString("%1").arg(ui->checkBox->isChecked()));
        if(!ui->lineEdit_1->text().isEmpty()) out.writeTextElement("caption", ui->lineEdit_1->text());
        out.writeStartElement("report");
            out.writeAttribute("width", QString("%1").arg(ui->spinBox_7->value()));
            out.writeAttribute("height", QString("%1").arg(ui->spinBox_8->value()));
        out.writeEndElement();
        out.writeStartElement("axis");
            out.writeAttribute("type", "absciss");
            if(!ui->lineEdit_2->text().isEmpty()) out.writeTextElement("caption", ui->lineEdit_2->text());
            out.writeTextElement("min",  QString("%1").arg(ui->doubleSpinBox_4->value()));
            out.writeTextElement("max",  QString("%1").arg(ui->doubleSpinBox_5->value()));
            out.writeTextElement("step", QString("%1").arg(ui->doubleSpinBox_6->value()));
        out.writeEndElement();
        out.writeStartElement("axis");
            out.writeAttribute("type", "ordinate");
            if(!ui->lineEdit_3->text().isEmpty()) out.writeTextElement("caption", ui->lineEdit_3->text());
            out.writeTextElement("min",  QString("%1").arg(ui->doubleSpinBox_3->value()));
            out.writeTextElement("max",  QString("%1").arg(ui->doubleSpinBox_2->value()));
            out.writeTextElement("step", QString("%1").arg(ui->doubleSpinBox->  value()));
        out.writeEndElement();
    out.writeEndElement();
}

//Read from XML
void AxesParameters::read(QXmlStreamReader& in)
{
    ui->checkBox->setChecked(in.attributes().value("is_autoscale").toString().toInt());
    while(!in.atEnd()){
        in.readNext();
        if(in.name() == "AxesParameters") break;
        if(in.tokenType() == QXmlStreamReader::StartElement){
            if(in.name() == "caption") ui->lineEdit_1->setText(in.readElementText());
            if(in.name() == "axis"){
                if(in.attributes().value("type") == "absciss") readAxis(in, ui->lineEdit_2, ui->doubleSpinBox_4, ui->doubleSpinBox_5, ui->doubleSpinBox_6);
                if(in.attributes().value("type") == "ordinate")readAxis(in, ui->lineEdit_3, ui->doubleSpinBox_3, ui->doubleSpinBox_2, ui->doubleSpinBox);
            }
            if(in.name() == "report"){
                ui->spinBox_7->setValue(in.attributes().value("width").toString().toInt());
                ui->spinBox_8->setValue(in.attributes().value("height").toString().toInt());
            }
        }
    }
}

void AxesParameters::readAxis(QXmlStreamReader& in, QLineEdit* caption, QDoubleSpinBox* m, QDoubleSpinBox* M, QDoubleSpinBox* s)
{
    while(!in.atEnd()){
        in.readNext();
        if(in.name() == "axis") break;
        if(in.tokenType() == QXmlStreamReader::StartElement){
            if(in.name() == "caption") caption->setText(in.readElementText());
            if(in.name() == "min")     m->setValue(in.readElementText().toDouble());
            if(in.name() == "max")     M->setValue(in.readElementText().toDouble());
            if(in.name() == "step")    s->setValue(in.readElementText().toDouble());
        }
    }
}
#include <QDebug>
QSize AxesParameters::canvasSizeInMm() const
{
    //Here we translate the size from mm to pixels.
    return QSize(ui->spinBox_7->value() * 3.77358, ui->spinBox_8->value() * 3.77358);
}

void AxesParameters::setStyleName(QString name)
{
    styleName = name;
    ui->lineEdit->setText(tr("Current style: ") + name);
    ui->lineEdit->setCursorPosition(0);
}

#include <QMouseEvent>
bool AxesParameters::eventFilter(QObject* target, QEvent* evt)
{
    if(evt->type() == QEvent::MouseButtonPress && (static_cast<QMouseEvent*>(evt)->button()) == Qt::LeftButton){
        //Absciss' interval
        if(target == ui->toolButton_7) foreach(AxesParameters* object, objects) object->ui->doubleSpinBox_4->setValue(ui->doubleSpinBox_4->value());
        if(target == ui->toolButton_5) foreach(AxesParameters* object, objects) object->ui->doubleSpinBox_5->setValue(ui->doubleSpinBox_5->value());
        if(target == ui->toolButton_6) foreach(AxesParameters* object, objects) object->ui->doubleSpinBox_6->setValue(ui->doubleSpinBox_6->value());
        //Ordinate's interval
        if(target == ui->toolButton_1) foreach(AxesParameters* object, objects) object->ui->doubleSpinBox_3->setValue(ui->doubleSpinBox_3->value());
        if(target == ui->toolButton_2) foreach(AxesParameters* object, objects) object->ui->doubleSpinBox_2->setValue(ui->doubleSpinBox_2->value());
        if(target == ui->toolButton_3) foreach(AxesParameters* object, objects) object->ui->doubleSpinBox->  setValue(ui->doubleSpinBox->value());
        //Report's size
        if(target == ui->toolButton_14)foreach(AxesParameters* object, objects) object->ui->spinBox_7->setValue(ui->spinBox_7->value());
        if(target == ui->toolButton_13)foreach(AxesParameters* object, objects) object->ui->spinBox_8->setValue(ui->spinBox_8->value());
        //Plot's titles
        if(target == ui->toolButton_8) foreach(AxesParameters* object, objects) object->ui->lineEdit_1->setText(ui->lineEdit_1->text());
        if(target == ui->toolButton_10)foreach(AxesParameters* object, objects) object->ui->lineEdit_2->setText(ui->lineEdit_2->text());
        if(target == ui->toolButton_9) foreach(AxesParameters* object, objects) object->ui->lineEdit_3->setText(ui->lineEdit_3->text());
        //Plot's style
        if(target == ui->toolButton)   foreach(AxesParameters* object, objects){object->setStyleName(styleName); emit object->setStyle(styleName);}
        //Autoscale
        if(target == ui->toolButton_16)foreach(AxesParameters* object, objects) object->ui->checkBox->setChecked(ui->checkBox->isChecked());
    }
    return QWidget::eventFilter(target, evt);
}
