#ifndef USER_REGISTRATIONS_CPP
#define USER_REGISTRATIONS_CPP

#include "client.h"
#include <string>
#include <QString>
#include <boost/filesystem.hpp>
bool Client::handleRegistration() { //Just registration, dont need to remember details of users.
    //Given user name and password to database functions.
    std::string username = this->data.user.userID ; //(this->registerpage->ui->txt_username)->text().toUtf8().constData();
    std::string passwd = this->data.user.password ; //((this->registerpage->ui->txt_password)->text()).toUtf8().constData();
    std::string clidir = this->data.user.clientDirectory; //((this->registerpage->ui->txt_clientDirectory)->text()).toUtf8().constData();

    if ( this->registrationRequest( username , passwd , clidir ) ) {
        //this->user.userID = username;
        //this->user.password = passwd;
        //this->user.clientDirectory = clidir;
        //this->user.serverDirectory = serdir;
        this->createFileLog(username , clidir);
        this->goBackToLoginPage();
        return true;
    } else {
        //TODO : Do Stuff. Invalid Login.
        QMessageBox msg;
        msg.setText(" Something ain't right \n");
        msg.exec();
        return false;
    }
}

bool Client::registrationRequest( std::string uid , std::string pw , std::string clidir) {
    std::string temp(REGISTRATION_REQUEST);
    conn.writeToSocket(temp); //Send the request.
    //Write to the socket.
    //sendRegistrationDetails()
    string cont;
    conn.readFromSocket(cont);
    UserDetails usr;
    usr.userID = uid;
    usr.password = pw;
    usr.clientDirectory = clidir;
    conn.writeToSocket_user(usr); //Write the socket onto the handler to check.
    //Now, to read back from the socket.
    std::string reply = "";
    conn.readFromSocket( reply ); //Somehwere in here, the server has checked the database for the user and replied.
    return (reply == REGISTRATION_ACCEPTED);
}

//Log files for owner's uploaded files and another for shared files.
bool Client::createFileLog(std::string uid ,  std::string clidir) {
    boost::filesystem::path dir(clidir);
    //Directory already exists.
    fstream maker( (uid).c_str() , ios::out );//, ios::app); MAKE IN THE CLIENT DIRECTORY ITSELF.
    maker.close();
    maker.open( (uid+SHARED_EXTN).c_str() , ios::out); //Creates file for shared files.
    maker.close();
}

#endif
