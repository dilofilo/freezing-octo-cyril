#ifndef USER_REGISTRATIONS_CPP
#define USER_REGISTRATIONS_CPP

#include "client.h"
#include <string>
#include <QString>
bool Client::handleRegistration() { //Just registration, dont need to remember details of users.
    //Given user name and password to database functions.
    std::string username = (this->registerpage->ui->txt_username)->text().toUtf8().constData();
    std::string passwd = ((this->registerpage->ui->txt_password)->text()).toUtf8().constData();
    std::string clidir = ((this->registerpage->ui->txt_clientDirectory)->text()).toUtf8().constData();
    std::string serdir = ""; // Not necessary, really.
    if ( this->registrationRequest( username , passwd , clidir ) ) {
//        this->user.userID = username;
//        this->user.password = passwd;
//        this->user.clientDirectory = clidir;
//        this->user.serverDirectory = serdir;
        //TODO : Do Stuff. Valid Login.
        this->goBackToLoginPage();
        return true;
    } else {
        //TODO : Do Stuff. Invalid Login.
        QMessageBox msg;
        msg.setText(" Invalid user name or password. Please try again \n");
        return false;
    }
}

bool Client::registrationRequest( std::string uid , std::string pw , std::string clidir) {
    std::string temp(REGISTRATION_REQUEST);
    conn.writeToSocket(temp);
    //Write to the socket.
    //Now, to read back from the socket.
    std::string reply = "";
    conn.readFromSocket( reply ); //Somehwere in here, the server has checked the database for the user and replied.
    return (reply == REGISTRATION_ACCEPTED);
}

#endif
