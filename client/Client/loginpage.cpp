#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>

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
    QMessageBox msgBox;
    if ( this->client->handlePing() ) {
        //Ping Successful!
        msgBox.setText("Ping successful! ");
    } else {
        //Ping Not Successful.
        msgBox.setText("Ping not successful! ");
    }
    msgBox.exec();
}

void LoginPage::on_btn_back_clicked()
{
    backToClientPage();
}

void LoginPage::backToClientPage() {
    this->hide();
    this->client->show();
}
