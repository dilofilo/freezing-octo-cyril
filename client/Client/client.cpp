#include "client.h"
#include "ui_client.h"

//UNNECESSARY INCLUDES. REMOVE SOON.
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

#include <QLineEdit>
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    //Assert : Presently, the client wants the IP Address.
}

Client::~Client()
{
    delete ui;
}

void Client::on_btn_launch_clicked()
{
    std::string serverip = ((this->ui->txt_serverip)->text()).toUtf8().constData(); //Gets the IP address of the user.
    QMessageBox msgBox;

    if ( this->prepareSocket(serverip) ) {
        //Get the socket and set it for all of its kids.
        //Create the login screen and give it the socket.
        msgBox.setText("Connection Successful! Press OK to move to the login page.");
        msgBox.exec(); //Exits when the user presses OK.
        this->openLoginPage(); //Well, thats the obvious step anyway.
    } else {
        //TODO: prepareSocket failed.
        msgBox.setText("Connection unsuccessful! Please check your IP Addresses and make sure that the appropriate PORT is open.");
        msgBox.exec();
    }
}

//Handles Connectivity Issues.
bool Client::prepareSocket(std::string serverAddressIP) {
    //Server address is the IP Address.
    //Take PORT as the predefined PORT.
    csock = socket(AF_INET, SOCK_STREAM , 0); //Creates the socket.
    if ( csock < 0 ) {
        return false;
    } else {

    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr( serverAddressIP.c_str());
    serverAddress.sin_port = PORT; //Predefined in INSTRUCTIONS.

    int rv = ::connect(csock, (struct sockaddr*) &serverAddress ,  sizeof(serverAddress)); // ::connect because Qt.
    if ( rv < 0 ) {
        return false;
    } else {
        return true; //Assert : connection created.
    }
}
