#include "dropbox.h"
#include "ui_dropbox.h"

DropBox::DropBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DropBox)
{
    ui->setupUi(this);
}

DropBox::~DropBox()
{
    delete ui;
}
