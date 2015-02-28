#ifndef DROPBOX_CPP
#define DROPBOX_CPP
#include "dropbox.h"
#include "ui_dropbox.h"
#include <QTreeView>
#include <QDirModel>
#include <QFileSystemModel>
#include "clientdefinitions.h"
DropBox::DropBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DropBox)
{
    ui->setupUi(this);
}

DropBox::DropBox(Client* _client , Socket& _csock , string sharedfiledir) { // NECESSARY CONSTERUCTOE.
    ui =  new Ui::DropBox();
    ui->setupUi(this);
    //this->setStyleSheet("background-color: black;");
    ui->serverTreeWidget->setColumnCount(1);
    client = _client;
    csock = _csock;
//    std::vector<QString> childName{"Java","CPP"};
//    AddRoot("Code",childName);
//    childName={"PL","CompArch"};
//    AddRoot("Assignments",childName);

    model = new QFileSystemModel(this);
    model->setReadOnly(false);
    QString sPath = QString::fromStdString(sharedfiledir);
    //dirmodel = new QFileSystemModel(this);
    //model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    model->setRootPath(sPath);





    //model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name );
     ui->clientTreeView->setModel(model);
     ui->clientTreeView->setRootIndex(model->setRootPath(sPath));

    QModelIndex index =model->index(QDir::currentPath());
    ui->clientTreeView->expand(index);
    ui->clientTreeView->scrollTo(index);
    ui->clientTreeView->setCurrentIndex((index));
    ui->clientTreeView->resizeColumnToContents(0);
    //ui->serverTreeView->setHeader("System Files");
}

DropBox::~DropBox()
{
    this->client->handleExit();
    delete ui;
}

void DropBox::AddRoot(QString Name, const std::vector<QString> childName)
{
    QTreeWidgetItem *itm= new QTreeWidgetItem(ui->serverTreeWidget);
    itm->setText(0,Name);
   // ui->copTreeWidget->addTopLevelItem(itm);
    AddChild(itm,childName[0]);
    AddChild(itm,childName[1]);
}

void DropBox::AddChild(QTreeWidgetItem *parent,QString Name)
{

    QTreeWidgetItem *itm= new QTreeWidgetItem();
    itm->setText(0,Name);
    //ui->treeWidget->addTopLevelItem(itm);
    parent->addChild(itm);

}


void DropBox::on_btnMake_clicked()
{

    QModelIndex index=ui->clientTreeView->currentIndex();
    if (!index.isValid())
        return;

    QString name = QInputDialog::getText(this,"Name","Enter a Name");

    if(name.isEmpty()) return;

    model->mkdir(index,name);
}

void DropBox::on_btnDelete_clicked()
{
    //delete
    QModelIndex index=ui->clientTreeView->currentIndex();
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

void DropBox::on_btnSearch_clicked()
{
    this->client->data.filename = this->ui->textSearch->text().toUtf8().constData();
    this->client->data.type = FILE_SEARCH;
    bool reply= this->client->eventHandler(FILE_SEARCH);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Search Failed"));
    }
}

void DropBox::on_btnUpload_clicked()
{

    this->client->data.type = UPLOAD_FILE;
    string pat = " hihihihih" + this->client->data.filename ;
    QString qpat = (model->filePath(this->ui->clientTreeView->currentIndex()));
    QMessageBox brk; brk.setText( qpat ); brk.exec();

    this->client->data.filename = (model->filePath(this->ui->clientTreeView->currentIndex())).toUtf8().constData();//this is a model index, convert to string
    bool reply= this->client->eventHandler(UPLOAD_FILE);
    if(!reply)
    {
        QMessageBox msg;
        msg.setText("File transfer error ");
        msg.exec();
    }
    else
    {
        //add it to the server dir.
        //this->ui->comboRevert->addItem("");//add stuff
    }
}

void DropBox::on_btnSync_clicked()
{
    this->client->data.type = SYNC;
    bool reply= this->client->eventHandler(SYNC);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Sync Failed"));
    }
}

void DropBox::on_btnLogout_clicked()
{
    bool reply= this->client->eventHandler(MAIN_TO_LOGIN);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Logout Failed"));
    }
}

void DropBox::on_btnExit_clicked()
{
    bool reply= this->client->eventHandler(MAIN_TO_DESKTOP);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Exit Failed"));
    }
}

void DropBox::on_btnDownload_clicked()
{
    this->client->data.filename = model->filePath(this->ui->serverTreeWidget->currentIndex()).toUtf8().constData(); //this is a model index, convert to string
    this->client->data.type = DOWNLOAD_FILE;
    bool reply= this->client->eventHandler(DOWNLOAD_FILE);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Download Failed"));
    }
}

void DropBox::on_btnRemove_clicked()
{
    this->client->data.filename = model->filePath(this->ui->serverTreeWidget->currentIndex()).toUtf8().constData();//this is a model index, convert to string
    this->client->data.type = REMOVE_FILE;
    bool reply= this->client->eventHandler(REMOVE_FILE);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Remove Failed"));
    }
}

void DropBox::on_btnShare_clicked()
{
    this->client->data.filename = model->filePath(this->ui->clientTreeView->currentIndex()).toUtf8().constData();//this is a model index, convert to string
    this->client->data.type = FILE_SHARE;
    bool reply= this->client->eventHandler( FILE_SHARE);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Share Failed"));
    }
}

void DropBox::on_btnUnshare_clicked()
{
    this->client->data.filename = model->filePath(this->ui->clientTreeView->currentIndex()).toUtf8().constData();//this is a model index, convert to string
    this->client->data.type = FILE_UNSHARE;
    QString userName= QInputDialog::getText(this,"User Name","Enter a Name");
    this->client->data.other_user.userID = userName.toUtf8().constData();

    bool reply= this->client->eventHandler( FILE_UNSHARE);

    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Unshare Failed"));
    }
}

void DropBox::on_btnConfirmRevert_clicked()
{
    this->client->data.fileversion = this->ui->comboRevert->currentText().toInt();
    this->client->data.filename  = this->ui->serverTreeWidget->currentIndex().data().toString().toUtf8().constData();
    this->client->data.type = REVERT;
    bool reply= this->client->eventHandler( REVERT);
    if(!reply)
    {
        QMessageBox::information(this,tr("Error"),tr("Share Failed"));
    }
}

void DropBox::updateServerFiles() {
    std::set<std::string>::iterator it = filenames.begin();
    this->ui->serverTreeWidget->clear();
    this->ui->shareTreeWidget->clear();
    for( ; it != filenames.end(); ++it) {
        //For each file name ,
        std::string fn1 = *it; //Gets the file name.
        std::string fo1 = fileowners[fn1];
        QString fn = QString::fromStdString(fn1);
        QString fo = QString::fromStdString(fo1);
        if ( fo1 == this->client->user.userID) {
            AddItem( fn );
        } else {
            AddItemShare( fn , fo );
        }
    }
}

void DropBox::on_shareTreeWidget_clicked(const QModelIndex &index)
{
    ui->comboRevert->clear();
    //int y=this->fileversions[toString(index->data())];
    ui->comboRevert->addItem("Version 1");//+QString::number(i));

}

void DropBox::AddItem(QString Name)
{
    QTreeWidgetItem *itm= new QTreeWidgetItem(ui->serverTreeWidget);
    itm->setText(0,Name); // itm->setText(1,size); // itm->setText(2,version);
}

void DropBox::AddItemShare(QString Name, QString Owner)
{
    QTreeWidgetItem *itm= new QTreeWidgetItem(ui->shareTreeWidget);
    itm->setText(0,Name); itm->setText(1,Owner);
}
#endif

void DropBox::on_serverTreeWidget_clicked(const QModelIndex &index)
{
    ui->comboRevert->clear();
    int y=this->fileversions[index.data().toString().toUtf8().constData()];
    for (int i=1;i<=y;i++)
    {
        ui->comboRevert->addItem("Version "+QString::number(i));
    }
}

void DropBox::on_textSearch_selectionChanged()
{
    this->ui->textSearch->setText("");
}
