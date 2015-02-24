#ifndef USER_LOGIN_CPP
#define USER_LOGIN_CPP
#include "client.h"
#include "ui_loginpage.h"

bool Client::handleLogin() {
    //Fetch Login details.
    std::string uid = (this->loginpage->ui->txt_username)->text().toUtf8.constData();
    std::string pw  = (this->loginpage->ui->txt_password)->text().toUtf8().constData();
    std::string clientDir = "";
    //Send login details to a function which returns a bool.
    bool validUser = this->sendLogin( uid , pw , clientDir); //No serverDir because thats on the end of the server.
    //return the value of the authenication
    if ( validUser ) {
        this->user.userID = uid;
        this->user.password = pw;
        this->user.clientDirectory = clientDir;
        return true;
    } else {
        return false;
    }
}

bool Client::handleLogout() {
    //Close the connection to the launch screen.
    close(csock);
    this->dropboxpage->hide();
    if ( this->loginpage != NULL ) { //possible segfault
        delete this->loginpage;
    }
    if ( this->registerpage != NULL ) { //possible segfault.
        delete this->registerpage;
    }
    if ( this->dropboxpage != NULL ) { //possible segfault.
        delete this->dropboxpage;
    }
    this->exitRequest();
    close(csock);
    this->show(); //Back to the square one.
    return true;
}

#endif
