/********************************************************************************
** Form generated from reading UI file 'dropbox.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DROPBOX_H
#define UI_DROPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DropBox
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DropBox)
    {
        if (DropBox->objectName().isEmpty())
            DropBox->setObjectName(QStringLiteral("DropBox"));
        DropBox->resize(640, 480);
        centralwidget = new QWidget(DropBox);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        DropBox->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(DropBox);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DropBox->setStatusBar(statusbar);

        retranslateUi(DropBox);

        QMetaObject::connectSlotsByName(DropBox);
    } // setupUi

    void retranslateUi(QMainWindow *DropBox)
    {
        DropBox->setWindowTitle(QApplication::translate("DropBox", "myDropBox", 0));
    } // retranslateUi

};

namespace Ui {
    class DropBox: public Ui_DropBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DROPBOX_H
