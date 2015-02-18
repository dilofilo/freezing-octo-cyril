/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *client)
    {
        if (client->objectName().isEmpty())
            client->setObjectName(QStringLiteral("client"));
        client->resize(1240, 745);
        centralWidget = new QWidget(client);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(300, 170, 641, 361));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        client->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(client);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1240, 25));
        client->setMenuBar(menuBar);
        mainToolBar = new QToolBar(client);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        client->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(client);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        client->setStatusBar(statusBar);

        retranslateUi(client);

        QMetaObject::connectSlotsByName(client);
    } // setupUi

    void retranslateUi(QMainWindow *client)
    {
        client->setWindowTitle(QApplication::translate("client", "client", 0));
    } // retranslateUi

};

namespace Ui {
    class client: public Ui_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
