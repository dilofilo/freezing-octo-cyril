#include "registerpage.h"
#include "ui_registerpage.h"

RegisterPage::RegisterPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
}

RegisterPage::~RegisterPage()
{
    delete ui;
}
