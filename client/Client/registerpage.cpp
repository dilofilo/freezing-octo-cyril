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
    //TODO TODO TODO
}
