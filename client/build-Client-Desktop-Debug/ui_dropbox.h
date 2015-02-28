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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DropBox
{
public:
    QWidget *centralwidget;
    QTreeView *clientTreeView;
    QPushButton *btnSync;
    QPushButton *btnDownload;
    QPushButton *btnRemove;
    QPushButton *btnShare;
    QPushButton *btnUnshare;
    QPushButton *btnUpload;
    QPushButton *btnMake;
    QPushButton *btnLogout;
    QPushButton *btnDelete;
    QPushButton *btnExit;
    QLineEdit *textSearch;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnSearch;
    QComboBox *comboRevert;
    QPushButton *btnConfirmRevert;
    QTreeWidget *serverTreeWidget;
    QTreeWidget *shareTreeWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DropBox)
    {
        if (DropBox->objectName().isEmpty())
            DropBox->setObjectName(QStringLiteral("DropBox"));
        DropBox->resize(1221, 734);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(48, 203, 237, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        DropBox->setPalette(palette);
        centralwidget = new QWidget(DropBox);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        clientTreeView = new QTreeView(centralwidget);
        clientTreeView->setObjectName(QStringLiteral("clientTreeView"));
        clientTreeView->setGeometry(QRect(690, 200, 371, 261));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush3(QColor(0, 255, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush3);
        QBrush brush4(QColor(159, 158, 158, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        QBrush brush5(QColor(240, 240, 240, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        clientTreeView->setPalette(palette1);
        btnSync = new QPushButton(centralwidget);
        btnSync->setObjectName(QStringLiteral("btnSync"));
        btnSync->setGeometry(QRect(390, 480, 99, 27));
        QPalette palette2;
        QBrush brush6(QColor(170, 0, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush6);
        QBrush brush7(QColor(0, 255, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush7);
        QBrush brush8(QColor(170, 85, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush8);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        btnSync->setPalette(palette2);
        btnDownload = new QPushButton(centralwidget);
        btnDownload->setObjectName(QStringLiteral("btnDownload"));
        btnDownload->setGeometry(QRect(260, 520, 99, 27));
        btnRemove = new QPushButton(centralwidget);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));
        btnRemove->setGeometry(QRect(390, 520, 99, 27));
        btnShare = new QPushButton(centralwidget);
        btnShare->setObjectName(QStringLiteral("btnShare"));
        btnShare->setGeometry(QRect(260, 560, 99, 27));
        btnUnshare = new QPushButton(centralwidget);
        btnUnshare->setObjectName(QStringLiteral("btnUnshare"));
        btnUnshare->setGeometry(QRect(390, 560, 99, 27));
        btnUpload = new QPushButton(centralwidget);
        btnUpload->setObjectName(QStringLiteral("btnUpload"));
        btnUpload->setGeometry(QRect(690, 480, 99, 27));
        btnMake = new QPushButton(centralwidget);
        btnMake->setObjectName(QStringLiteral("btnMake"));
        btnMake->setGeometry(QRect(690, 520, 99, 27));
        btnLogout = new QPushButton(centralwidget);
        btnLogout->setObjectName(QStringLiteral("btnLogout"));
        btnLogout->setGeometry(QRect(690, 560, 99, 27));
        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(820, 520, 99, 27));
        btnExit = new QPushButton(centralwidget);
        btnExit->setObjectName(QStringLiteral("btnExit"));
        btnExit->setGeometry(QRect(820, 560, 99, 27));
        textSearch = new QLineEdit(centralwidget);
        textSearch->setObjectName(QStringLiteral("textSearch"));
        textSearch->setGeometry(QRect(850, 60, 201, 27));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 170, 121, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(690, 170, 241, 16));
        btnSearch = new QPushButton(centralwidget);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setGeometry(QRect(760, 60, 99, 27));
        comboRevert = new QComboBox(centralwidget);
        comboRevert->setObjectName(QStringLiteral("comboRevert"));
        comboRevert->setGeometry(QRect(120, 60, 121, 27));
        btnConfirmRevert = new QPushButton(centralwidget);
        btnConfirmRevert->setObjectName(QStringLiteral("btnConfirmRevert"));
        btnConfirmRevert->setGeometry(QRect(250, 60, 101, 27));
        serverTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        serverTreeWidget->setHeaderItem(__qtreewidgetitem);
        serverTreeWidget->setObjectName(QStringLiteral("serverTreeWidget"));
        serverTreeWidget->setGeometry(QRect(110, 200, 381, 261));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        serverTreeWidget->setPalette(palette3);
        shareTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        shareTreeWidget->setHeaderItem(__qtreewidgetitem1);
        shareTreeWidget->setObjectName(QStringLiteral("shareTreeWidget"));
        shareTreeWidget->setGeometry(QRect(10, 490, 241, 181));
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
        btnSync->setText(QApplication::translate("DropBox", "Sync", 0));
        btnDownload->setText(QApplication::translate("DropBox", "Download", 0));
        btnRemove->setText(QApplication::translate("DropBox", "Remove", 0));
        btnShare->setText(QApplication::translate("DropBox", "Share", 0));
        btnUnshare->setText(QApplication::translate("DropBox", "Unshare", 0));
        btnUpload->setText(QApplication::translate("DropBox", "Upload", 0));
        btnMake->setText(QApplication::translate("DropBox", "MakeDir", 0));
        btnLogout->setText(QApplication::translate("DropBox", "LogOut", 0));
        btnDelete->setText(QApplication::translate("DropBox", "Delete", 0));
        btnExit->setText(QApplication::translate("DropBox", "Exit", 0));
        label->setText(QApplication::translate("DropBox", "Server Files", 0));
        label_2->setText(QApplication::translate("DropBox", "Client Files", 0));
        btnSearch->setText(QApplication::translate("DropBox", "Search", 0));
        comboRevert->clear();
        comboRevert->insertItems(0, QStringList()
         << QApplication::translate("DropBox", "Version 1", 0)
        );
        btnConfirmRevert->setText(QApplication::translate("DropBox", "Revert!", 0));
    } // retranslateUi

};

namespace Ui {
    class DropBox: public Ui_DropBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DROPBOX_H
