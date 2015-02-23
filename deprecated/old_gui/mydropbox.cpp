#include "mydropbox.h"
#include "ui_mydropbox.h"
#include <QDirModel>

myDropBox::myDropBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myDropBox)
{
    ui->setupUi(this);
    ui->treeWidgetDir->setColumnCount(1);
    std::vector<QString> childName{"Java","CPP"};
    AddRoot("Code",childName);
    childName={"PL","CompArch"};
    AddRoot("Assignments",childName);

    model = new QDirModel(this);
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name );
     ui->treeViewFiles->setModel(model);
    QModelIndex index =model->index("/home/dual/cs5130287/Desktop");
    ui->treeViewFiles->expand(index);
    ui->treeViewFiles->scrollTo(index);
    ui->treeViewFiles->setCurrentIndex((index));
    ui->treeViewFiles->resizeColumnToContents(0);
    ui->treeWidgetDir->setHeaderLabel("System Files");
}

myDropBox::~myDropBox()
{
    delete ui;
}

void myDropBox::AddRoot(QString Name, const std::vector<QString> childName)
{
    QTreeWidgetItem *itm= new QTreeWidgetItem(ui->treeWidgetDir);
    itm->setText(0,Name);
   // ui->copTreeWidget->addTopLevelItem(itm);
    AddChild(itm,childName[0]);
    AddChild(itm,childName[1]);
}

void myDropBox::AddChild(QTreeWidgetItem *parent,QString Name)
{

    QTreeWidgetItem *itm= new QTreeWidgetItem();
    itm->setText(0,Name);
    //ui->treeWidget->addTopLevelItem(itm);
    parent->addChild(itm);

}
void myDropBox::on_btnMake_clicked()
{
    QModelIndex index=ui->treeViewFiles->currentIndex();
    if (!index.isValid())
        return;

    QString name = QInputDialog::getText(this,"Name","Enter a Name");

    if(name.isEmpty()) return;

    model->mkdir(index,name);
}

void myDropBox::on_btnDelete_clicked()
{
    //delete
    QModelIndex index=ui->treeViewFiles->currentIndex();
    if (!index.isValid())
        return;

    if (model->fileInfo(index).isDir())
    {
        model->rmdir(index);
    }
    else
    {
        model->remove(index);
    }
}
