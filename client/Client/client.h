#ifndef CLIENT_H
#define CLIENT_H
using namespace std;
#include <QMainWindow>
//Connectivity Stuff
#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include "arpa/inet.h"
#include <iostream>
#include "../../common/instructions.h"
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#define CLIENT_SIDE
#include "../../common/instructions.h"
#include "../../common/communications.h" //does typedef int Socket.

//Client related files.
#include "loginpage.h"
#include "registerpage.h"
#include "dropbox.h"

namespace Ui {
class Client;
class LoginPage;
class RegisterPage;
class DropBox;
}

class Client : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    
private slots:
    void on_btn_launch_clicked();

private:
    //Socket creation things.
    Socket csock;
    struct sockaddr_in serverAddress, clientAddress;
    struct hostent* server_entity;
    std::string serverAddress_string;

    //UI Related object pointers. To be initialized upon connection.
    Ui::Client *ui; //Disabled after creation
    Ui::LoginPage *loginpage; //Show first.
    Ui::RegisterPage *registerpage; //Shown if registration is clicked.
    Ui::DropBox *dropboxpage; //Show after successful login.

    //Connection functions.
    bool prepareSocket(std::string serveraddress);
};

#endif // CLIENT_H
