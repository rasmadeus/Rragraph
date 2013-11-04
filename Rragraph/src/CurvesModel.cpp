#include "CurvesModel.h"

#include "Files.h"
#include "HeaderSamples.h"
CurvesModel::CurvesModel(QObject *parent) :
    QAbstractTableModel(parent),
    curves(nullptr)
{
    connect(Files::getInstance(), SIGNAL(wasLoaded(int)), SLOT(wasLoaded(int)));
    connect(
        HeaderSamples::getInstance(),
        SIGNAL(headerWasChanged(int,int,QString)),
        SLOT(headerWasChanged(int,int,QString))
    );
}

Qt::ItemFlags CurvesModel::flags(const QModelIndex& index) const{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

Curves* CurvesModel::getCurves() const{
    return curves;
}

#include "Curves.h"
void CurvesModel::setCurves(Curves* curves)
{
    beginResetModel();
        this->curves = curves;
    endResetModel();
}

int CurvesModel::rowCount(const QModelIndex& parent) const{
    Q_UNUSED(parent)
    return curves && !curves->isLoading() ? curves->rowCount() : 0;
}

int CurvesModel::columnCount(const QModelIndex& parent) const{
    Q_UNUSED(parent)
    return !curves || curves->isLoading() ? 0 : 5;
}

QVariant CurvesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(section){
            case 0 : return QObject::tr("Absciss");
            case 1 : return QObject::tr("Ordinates");
            case 2 : return QObject::tr("Color");
            case 3 : return QObject::tr("Scale");
            case 4 : return QObject::tr("Other");
        };
    }
    return QVariant();
}

#include "Curve.h"
bool CurvesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(role != Qt::EditRole){
        return false;
    }
    beginResetModel();
       switch(index.column()){
            case 0: curves->setX(index.row());                            break;
            case 1: curves->setY(index.row());                            break;
            case 2: curves->setColor(index.row(), value.value<QColor>()); break;
            case 3: curves->setScale(index.row(), value.toDouble());      break;
            case 4: curves->update(index.row());                          break;
        }
    endResetModel();
    return true;
}

static QString displayRole(int column, int row, Curves* curves)
{  
    switch(column){
        case 0: return curves->getHeader(row);
        case 1: return curves->isY(row) ? QObject::tr("Yes") : QObject::tr("No");
        case 3: return QString("%1").arg(curves->isY(row) ? curves->getCurve(row)->getMultY() : 1);
        case 4: return QObject::tr("other");
    }
    return QString();
}

static QFont fontRole(int column, int row, Curves* curves)
{
    static QFont active;
    active.setBold(true);
    active.setPointSize(QFont().pointSize() + 2);

    switch(column){
        case 0: return curves->isX(row) ? active : QFont();
        case 1: return curves->isY(row) ? active : QFont();
    }

    return QFont();
}

static QColor textColorRole(int column, int row, Curves* curves)
{
    switch(column){
        case 0: return QColor(curves->isX(row) ? "red" : "black");
        case 1: return QColor(curves->isY(row) ? "red" : "black");
    }
    return QColor("black");
}

static QColor backgroundRole(int column, int row, Curves* curves)
{
    switch(column){
        case 2: return curves->isY(row) ? curves->getCurve(row)->pen().color() : QColor("gray");
    }
    return QColor("white");
}

QVariant CurvesModel::data(const QModelIndex& index, int role) const
{
    switch(role){
        case Qt::DisplayRole :    return displayRole(   index.column(), index.row(), curves);
        case Qt::FontRole :       return fontRole(      index.column(), index.row(), curves);
        case Qt::TextColorRole:   return textColorRole( index.column(), index.row(), curves);
        case Qt::BackgroundRole : return backgroundRole(index.column(), index.row(), curves);
    }

    return QVariant();
}

void CurvesModel::wasLoaded(int iFile)
{
    if(!curves){
        return;
    }
    beginResetModel();
        curves->wasLoaded(iFile);
    endResetModel();
}

void CurvesModel::headerWasChanged(int iFile, int i, const QString& header)
{
    if(!curves){
        return;
    }
    curves->headerWasChanged(iFile, i, header);
}
