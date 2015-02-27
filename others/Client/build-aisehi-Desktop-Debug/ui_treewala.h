/********************************************************************************
** Form generated from reading UI file 'treewala.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEWALA_H
#define UI_TREEWALA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_treewala
{
public:
    QWidget *centralwidget;
    QTreeWidget *copTreeWidget;
    QTreeView *copTreeView;
    QPushButton *btnMake;
    QPushButton *btnDelete;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLineEdit *lineEdit;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *treewala)
    {
        if (treewala->objectName().isEmpty())
            treewala->setObjectName(QStringLiteral("treewala"));
        treewala->resize(800, 600);
        centralwidget = new QWidget(treewala);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        copTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        copTreeWidget->setHeaderItem(__qtreewidgetitem);
        copTreeWidget->setObjectName(QStringLiteral("copTreeWidget"));
        copTreeWidget->setGeometry(QRect(50, 91, 271, 261));
        copTreeView = new QTreeView(centralwidget);
        copTreeView->setObjectName(QStringLiteral("copTreeView"));
        copTreeView->setGeometry(QRect(440, 90, 291, 261));
        btnMake = new QPushButton(centralwidget);
        btnMake->setObjectName(QStringLiteral("btnMake"));
        btnMake->setGeometry(QRect(440, 410, 99, 27));
        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(550, 410, 99, 27));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 410, 99, 27));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 410, 99, 27));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 60, 91, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(440, 60, 91, 17));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(440, 370, 99, 27));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(440, 450, 99, 27));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(438, 10, 99, 27));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(530, 10, 131, 27));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(220, 370, 99, 27));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(550, 450, 99, 27));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(90, 450, 99, 27));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(220, 450, 101, 27));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(50, 10, 161, 27));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 10, 67, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(660, 10, 21, 31));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../../ico_search_smaller.png")));
        treewala->setCentralWidget(centralwidget);
        menubar = new QMenuBar(treewala);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        treewala->setMenuBar(menubar);
        statusbar = new QStatusBar(treewala);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        treewala->setStatusBar(statusbar);

        retranslateUi(treewala);

        QMetaObject::connectSlotsByName(treewala);
    } // setupUi

    void retranslateUi(QMainWindow *treewala)
    {
        treewala->setWindowTitle(QApplication::translate("treewala", "myDropBox", 0));
        btnMake->setText(QApplication::translate("treewala", "MakeDir", 0));
        btnDelete->setText(QApplication::translate("treewala", "Delete", 0));
        pushButton->setText(QApplication::translate("treewala", "Download", 0));
        pushButton_2->setText(QApplication::translate("treewala", "Remove", 0));
        label->setText(QApplication::translate("treewala", "Server Side", 0));
        label_2->setText(QApplication::translate("treewala", "Client Side", 0));
        pushButton_3->setText(QApplication::translate("treewala", "Upload", 0));
        pushButton_5->setText(QApplication::translate("treewala", "LogOut", 0));
        pushButton_6->setText(QApplication::translate("treewala", "Search", 0));
        lineEdit->setText(QApplication::translate("treewala", "Search For", 0));
        pushButton_7->setText(QApplication::translate("treewala", "Sync", 0));
        pushButton_8->setText(QApplication::translate("treewala", "Exit", 0));
        pushButton_9->setText(QApplication::translate("treewala", "Share", 0));
        lineEdit_2->setText(QApplication::translate("treewala", "User", 0));
        label_3->setText(QApplication::translate("treewala", "Revert to", 0));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class treewala: public Ui_treewala {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEWALA_H
