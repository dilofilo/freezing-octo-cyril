#ifndef USER_LOGIN_CPP
#define USER_LOGIN_CPP
#include "client.h"
#include "ui_loginpage.h"

bool Client::handleLogin() {
    //Fetch Login details. - Done in the caller for this.
    //Send login details to a function which returns a bool.
    bool validUser = this->sendLogin( data.user.userID , data.user.password , data.user.clientDirectory); //No serverDir because thats on the end of the server.
    //return the value of the authenication
    if ( validUser ) {
        this->user.userID = data.user.userID;
        this->user.password = data.user.password;
        this->user.clientDirectory = data.user.clientDirectory; //NEED TO GET FROM THE SERVER.
        //Dont need server directory for the client.
        //TODO : Fetch the file system
        return true;
    } else {
        this->user.userID = "";
        this->user.password = "";
        this->user.clientDirectory = "";
        //TODO : Do Nothing.
        return false;
    }
}

bool Client::handleLogout() {
    // to the launch screen.
    this->show(); //Back to the square one.
    if ( this->dropboxpage != NULL ) delete this->dropboxpage;
    return true;
}


/*
    MINION FUNCTIONS!
*/

bool Client::sendLogin( std::string& uid , std::string& pw , std::string& clidir) {
    //Write to the server and get the details back.
    /*
     *Send login request, read continue, send user details , read reply login details, read rejection/acceptance.
     */
    std::string temp( LOGIN_REQUEST );
    conn.writeToSocket(temp);
    //Read a continue.
    std::string temp2 = "";
    conn.readFromSocket(temp2);
    if ( !(temp2 == CONTINUE) ) {
        return false;
    }
    //Send User details function.
    conn.writeToSocket_user(data.user);
    UserDetails tempusr;
    conn.readFromSocket_user(tempusr);
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    conn.readFromSocket(temp2);
    if ( temp2 == LOGIN_ACCEPTED ) {
        data.user = tempusr;
        return true; //Saved on server side.
    } else {
        return false;
    }

}

#endif
