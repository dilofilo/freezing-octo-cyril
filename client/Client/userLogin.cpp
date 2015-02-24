#ifndef USER_LOGIN_CPP
#define USER_LOGIN_CPP
#include "client.h"
#include "ui_loginpage.h"

bool Client::handleLogin() {
    //Fetch Login details. - Done in the caller for this.
    //Send login details to a function which returns a bool.
    bool validUser = this->sendLogin( user.userID , user.password , user.clientDirectory); //No serverDir because thats on the end of the server.
    //return the value of the authenication
    if ( validUser ) {
        return true;
    } else {
        this->user.userID = "";
        this->user.password = "pw";
        this->user.clientDirectory = "";

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


/*
    MINION FUNCTIONS!
*/

bool Client::sendLogin( std::string& uid , std::string& pw , std::string& clidir) {
    //Write to the server and get the details back.
    std::string temp( LOGIN_REQUEST );
    conn.writeToSocket(temp);
    //Send User details function.

}

#endif
