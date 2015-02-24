#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>
#include <iostream>
LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::LoginPage(Client * _client , Socket& _csock) : ui(new Ui::LoginPage) {
    csock = _csock;
    client = _client;
    ui->setupUi(this); //necessary, I think.
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_btn_ping_clicked()
{

    bool reply = this->client->handlePing();
    QMessageBox msg;
    if (reply) {
        msg.setText("success!\n");
    } else {
        msg.setText("failure!\n");
    }
    msg.exec();
}

void LoginPage::on_btn_back_clicked()
{
    backToClientPage();
}

void LoginPage::backToClientPage() {
    this->hide();
    this->client->show();
}

void LoginPage::on_btn_register_clicked()
{
    goToRegisterPage();
}
