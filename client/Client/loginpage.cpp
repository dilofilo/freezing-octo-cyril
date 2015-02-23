#include "loginpage.h"
#include "ui_loginpage.h"

#include "clientping.cpp" //Tells you how to ping.
LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_btn_ping_clicked()
{
    if ( handlePing( csock ) ) {
        //Ping Successful!
    } else {
        //Ping Not Successful.
    }
}
