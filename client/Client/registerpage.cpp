#ifndef REGISTER_PAGE_CPP
#define REGISTER_PAGE_CPP
#include "registerpage.h"
#include "ui_registerpage.h"
#include <QMessageBox>
RegisterPage::RegisterPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
}

RegisterPage::RegisterPage(Client* _client , Socket& _csock) {
    ui =  new Ui::RegisterPage;
    client = _client;
    csock = _csock;
    ui->setupUi(this);
}

RegisterPage::~RegisterPage()
{
    this->client->handleExit();
    delete ui;
}

void RegisterPage::on_btn_registerConfirm_clicked()
{
    //Set the data.
    this->client->data.type = REGISTER_TO_LOGIN_REGISTER;
    this->client->data.user.userID = ((this->ui->txt_username)->text()).toUtf8().constData();
    this->client->data.user.password = ((this->ui->txt_password)->text()).toUtf8().constData();
    this->client->data.user.clientDirectory = ((this->ui->txt_clientDirectory)->text()).toUtf8().constData();
    //Passes data across.
    bool reply = this->client->eventHandler(REGISTER_TO_LOGIN_REGISTER);
    if (!reply) {
        //Something bad has happened.
        QMessageBox msgBox;
        msgBox.setText(" Registration Failed - chances are, somebody has the same username as you ");
        msgBox.exec();
    } //Done?
}



void RegisterPage::on_btn_ping_clicked()
{
    //call the ping function of the client.
    bool success = this->client->eventHandler(PING_INSTR);
    QMessageBox msg;
    if (success) {
        msg.setText("success!");
    } else {
        msg.setText("failure :(");
    }
    msg.exec();
} //Done.


void RegisterPage::on_btn_back_clicked()
{
    //Should go back to the login page.
    this->client->eventHandler( REGISTER_TO_LOGIN_BACK ); //Nothing ought to go wrng.
}
#endif
