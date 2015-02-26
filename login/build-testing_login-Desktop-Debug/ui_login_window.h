/********************************************************************************
** Form generated from reading UI file 'login_window.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_WINDOW_H
#define UI_LOGIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login_Window
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Login_Window)
    {
        if (Login_Window->objectName().isEmpty())
            Login_Window->setObjectName(QStringLiteral("Login_Window"));
        Login_Window->resize(400, 318);
        centralWidget = new QWidget(Login_Window);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 156, 231, 51));
        Login_Window->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Login_Window);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        Login_Window->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Login_Window);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Login_Window->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Login_Window);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Login_Window->setStatusBar(statusBar);

        retranslateUi(Login_Window);

        QMetaObject::connectSlotsByName(Login_Window);
    } // setupUi

    void retranslateUi(QMainWindow *Login_Window)
    {
        Login_Window->setWindowTitle(QApplication::translate("Login_Window", "Login_Window", 0));
        label->setText(QApplication::translate("Login_Window", "Status", 0));
    } // retranslateUi

};

namespace Ui {
    class Login_Window: public Ui_Login_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_WINDOW_H
