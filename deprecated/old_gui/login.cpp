#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnSignIn_clicked()
{
    dropBox=new myDropBox(this);
    dropBox->show();
}

void Login::on_btnRegister_clicked()
{
    reg=new Register(this);
    reg->show();
}
