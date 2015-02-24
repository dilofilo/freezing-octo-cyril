#include "registerpage.h"
#include "ui_registerpage.h"

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
    this->client->exit();
    delete ui;
}

void RegisterPage::on_btn_registerConfirm_clicked()
{
    //Set the data.
    this->client->data.type = REGISTER_TO_LOGIN_REGISTER;
    this->client->data.user.userID = (this->ui->txt_username)->text();
    this->client->data.user.password = (this->ui->txt_password)->text();
    this->client->data.user.clientDirectory = (this->ui->txt_clientDirectory)->text();
    //Passes data across.
    bool reply = this->client->eventHandler(REGISTER_TO_LOGIN_REGISTER);
    if (!reply) {
        //Something bad has happened.
        QMessageBox msgBox;
        msgBox.setText(" Registration Failed - chances are, somebody has the same username as you ");
        msgBox.exec();
    }
}
