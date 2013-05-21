/********************************************************************************
** Form generated from reading UI file 'StylesEditor.ui'
**
** Created: Tue 16. Apr 10:10:42 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STYLESEDITOR_H
#define UI_STYLESEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StylesEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButton_7;
    QToolButton *toolButton_6;
    QSpacerItem *verticalSpacer;
    QToolButton *toolButton_5;
    QToolButton *toolButton_4;
    QToolButton *toolButton_3;
    QToolButton *toolButton;
    QToolButton *toolButton_2;

    void setupUi(QDialog *StylesEditor)
    {
        if (StylesEditor->objectName().isEmpty())
            StylesEditor->setObjectName(QString::fromUtf8("StylesEditor"));
        StylesEditor->setWindowModality(Qt::NonModal);
        StylesEditor->resize(482, 349);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/MainWindow/Options/styles_editor.png"), QSize(), QIcon::Normal, QIcon::Off);
        StylesEditor->setWindowIcon(icon);
        StylesEditor->setModal(true);
        horizontalLayout = new QHBoxLayout(StylesEditor);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeView = new QTreeView(StylesEditor);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        treeView->setAlternatingRowColors(false);
        treeView->setAnimated(true);
        treeView->setAllColumnsShowFocus(false);
        treeView->setWordWrap(false);
        treeView->header()->setCascadingSectionResizes(false);

        horizontalLayout->addWidget(treeView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButton_7 = new QToolButton(StylesEditor);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/Canvas/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_7->setIcon(icon1);
        toolButton_7->setIconSize(QSize(18, 18));

        verticalLayout_2->addWidget(toolButton_7);

        toolButton_6 = new QToolButton(StylesEditor);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/Styles/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_6->setIcon(icon2);
        toolButton_6->setIconSize(QSize(18, 18));

        verticalLayout_2->addWidget(toolButton_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        toolButton_5 = new QToolButton(StylesEditor);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/Styles/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_5->setIcon(icon3);
        toolButton_5->setIconSize(QSize(18, 18));

        verticalLayout_2->addWidget(toolButton_5);

        toolButton_4 = new QToolButton(StylesEditor);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/Styles/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon4);
        toolButton_4->setIconSize(QSize(18, 18));

        verticalLayout_2->addWidget(toolButton_4);

        toolButton_3 = new QToolButton(StylesEditor);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/Styles/update.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon5);
        toolButton_3->setIconSize(QSize(18, 18));

        verticalLayout_2->addWidget(toolButton_3);

        toolButton = new QToolButton(StylesEditor);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/Styles/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon6);
        toolButton->setIconSize(QSize(18, 18));

        verticalLayout_2->addWidget(toolButton);

        toolButton_2 = new QToolButton(StylesEditor);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/Styles/import.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon7);
        toolButton_2->setIconSize(QSize(18, 18));

        verticalLayout_2->addWidget(toolButton_2);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(StylesEditor);

        QMetaObject::connectSlotsByName(StylesEditor);
    } // setupUi

    void retranslateUi(QDialog *StylesEditor)
    {
        StylesEditor->setWindowTitle(QApplication::translate("StylesEditor", "The style's editor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        treeView->setToolTip(QApplication::translate("StylesEditor", "In this place showing the current group's styles.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        treeView->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        treeView->setWhatsThis(QApplication::translate("StylesEditor", "In this place showing the current group's styles.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        toolButton_7->setToolTip(QApplication::translate("StylesEditor", "Show next style's group. If you didn't save the styles then your changes will be lost.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        toolButton_7->setWhatsThis(QApplication::translate("StylesEditor", "Show next style's group. If you didn't save the styles then your changes will be lost.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton_7->setText(QString());
#ifndef QT_NO_STATUSTIP
        toolButton_6->setStatusTip(QApplication::translate("StylesEditor", "Save your changes to register.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        toolButton_6->setWhatsThis(QApplication::translate("StylesEditor", "Save your changes to register.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton_6->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_5->setToolTip(QApplication::translate("StylesEditor", "Insert new style. Current position have to be root.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolButton_5->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        toolButton_5->setWhatsThis(QApplication::translate("StylesEditor", "Insert new style. Current position have to be root.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton_5->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_4->setToolTip(QApplication::translate("StylesEditor", "Remove current style. Current position have to be root.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        toolButton_4->setWhatsThis(QApplication::translate("StylesEditor", "Remove current style. Current position have to be root.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton_4->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_3->setToolTip(QApplication::translate("StylesEditor", "Reopen current styles' group.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        toolButton_3->setWhatsThis(QApplication::translate("StylesEditor", "Reopen current styles' group.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton->setToolTip(QApplication::translate("StylesEditor", "Export current styles' group to file.ini", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        toolButton->setWhatsThis(QApplication::translate("StylesEditor", "Export current styles' group to file.ini", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_2->setToolTip(QApplication::translate("StylesEditor", "Import current styles' group from file.ini", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        toolButton_2->setWhatsThis(QApplication::translate("StylesEditor", "Import current styles' group from file.ini", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StylesEditor: public Ui_StylesEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STYLESEDITOR_H
