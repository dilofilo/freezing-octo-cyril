#ifndef DROPBOX_H
#define DROPBOX_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QtCore>
#include <QtGui>
#include <vector>
#include <QDirModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QLineEdit>

class Client;

#include "../../common/instructions.h"
#include "../../common/communications.h" //Defines socket.


namespace Ui {
class DropBox;
}

class DropBox : public QMainWindow
{
    Q_OBJECT
    void AddRoot(QString Name, const std::vector<QString> childName);
    void AddChild(QTreeWidgetItem *parent,QString Name);
    
public:
    explicit DropBox(QWidget *parent = 0);
    DropBox(Client* _client , Socket& _csock);
    ~DropBox();
    
private slots:
    void on_btnMake_clicked();

    void on_btnDelete_clicked();
    void on_btnUnshare_clicked();
    void on_btnConfirmRevert_clicked();

    void on_btnSearch_clicked();

    void on_btnUpload_clicked();

    void on_btnSync_clicked();

    void on_btnLogout_clicked();

    void on_btnExit_clicked();

    void on_btnDownload_clicked();

    void on_btnRemove_clicked();

    void on_btnShare_clicked();

private:
    Client* client;
    Socket csock;
    Ui::DropBox *ui;
    QDirModel *model;
};

#include "client.h" //Safe because forward declarations and header guards.
#endif // DROPBOX_H

