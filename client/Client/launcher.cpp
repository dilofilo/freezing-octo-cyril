#ifndef LAUNCHER_CPP
#define LAUNCHER_CPP

#include "client.h"

void Client::launch() {
    std::string serverip = ((this->ui->txt_serverip)->text()).toUtf8().constData(); //Gets the IP address of the user.
    QMessageBox msgBox;

    if ( this->prepareSocket(serverip) ) {
        //Get the socket and set it for all of its kids.
        //Create the login screen and give it the socket.

        if (this->createPages()) { //Creates the LOGIN PAGE here.
            this->showLoginPage(); // Shows the LOGIN PAGE here.
        } else {
            msgBox.setText(" can't open the login page. Dont ask me please.");
            msgBox.exec();
        }
    } else {
        //TODO: prepareSocket failed.
        msgBox.setText("Connection unsuccessful! Please check your IP Addresses and make sure that the appropriate PORT is open.");
        msgBox.exec();
    }
}

void Client::unlaunch() {
    this->loginpage->hide(); //MEMORY LEAK?
    this->show();
}
//Creation of login page.
bool Client::createPages() {
    return true;
}
void Client::showLoginPage() {
    this->hide();
    this->loginpage->show();
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
        conn.setSocket(csock);
        return true; //Assert : connection created.
    }
}

#endif
