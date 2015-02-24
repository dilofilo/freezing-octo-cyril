#ifndef DROPBOX_H
#define DROPBOX_H

#include <QMainWindow>

class Client;

#include "../../common/instructions.h"
#include "../../common/communications.h" //Defines socket.

namespace Ui {
class DropBox;
}

class DropBox : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DropBox(QWidget *parent = 0);
    DropBox(QMainWindow* client);
    DropBox(Socket& _csock);
    ~DropBox();
    
private:
    Client* client;
    Socket csock;
    Ui::DropBox *ui;
};

#include "client.h" //Safe because forward declarations and header guards.
#endif // DROPBOX_H
