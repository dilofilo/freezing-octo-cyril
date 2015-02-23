/********************************************************************************
** Form generated from reading UI file 'loginpage.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLineEdit *txt_username;
    QLineEdit *txt_password;
    QPushButton *btn_login;
    QPushButton *btn_register;
    QPushButton *btn_ping;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName(QStringLiteral("LoginPage"));
        LoginPage->resize(319, 210);
        centralwidget = new QWidget(LoginPage);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(19, 29, 271, 111));
        txt_username = new QLineEdit(groupBox);
        txt_username->setObjectName(QStringLiteral("txt_username"));
        txt_username->setGeometry(QRect(10, 30, 161, 29));
        txt_password = new QLineEdit(groupBox);
        txt_password->setObjectName(QStringLiteral("txt_password"));
        txt_password->setGeometry(QRect(10, 80, 161, 29));
        txt_password->setInputMask(QStringLiteral(""));
        btn_login = new QPushButton(groupBox);
        btn_login->setObjectName(QStringLiteral("btn_login"));
        btn_login->setGeometry(QRect(160, 80, 101, 27));
        btn_register = new QPushButton(groupBox);
        btn_register->setObjectName(QStringLiteral("btn_register"));
        btn_register->setGeometry(QRect(160, 30, 101, 27));
        btn_ping = new QPushButton(centralwidget);
        btn_ping->setObjectName(QStringLiteral("btn_ping"));
        btn_ping->setGeometry(QRect(30, 160, 251, 27));
        LoginPage->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(LoginPage);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LoginPage->setStatusBar(statusbar);

        retranslateUi(LoginPage);

        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QMainWindow *LoginPage)
    {
        LoginPage->setWindowTitle(QApplication::translate("LoginPage", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("LoginPage", "yourLoginBox", 0));
        txt_username->setText(QApplication::translate("LoginPage", "username?", 0));
        txt_password->setText(QApplication::translate("LoginPage", "password?", 0));
        btn_login->setText(QApplication::translate("LoginPage", "Login!", 0));
        btn_register->setText(QApplication::translate("LoginPage", "Register!", 0));
        btn_ping->setText(QApplication::translate("LoginPage", "Ping!", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
