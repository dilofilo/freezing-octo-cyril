#ifndef LOGIN_CPP
#define LOGIN_CPP
#include"server.h"
#include"../../common/communications.h"
#include"../../common/instructions.h"
#include <string>

bool Server::handleLogin()
{
    cout << "entered handleLogin() \n";
    string cont( CONTINUE );
    cout << "writing continue \n";
    conn.writeToSocket(cont);
    struct UserDetails usr;
    cout << "reading user \n";
    conn.readFromSocket_user( usr );
    cout << "read user with id=" << usr.userID << "and pw=" << usr.password << "\n";
    if( authenticate(usr) ) { //Login was correct
        //Authentication Successful.
        cout << "authentication successfuly \n";
        conn.writeToSocket_user(usr);

        std::string temp;
        conn.readFromSocket(temp); //CONTINUE STATEMENT
        user = usr;
        std::string accepted( LOGIN_ACCEPTED );
        conn.writeToSocket(accepted);
        handleSync();       // Sending the info on all files the client has access to. TODO
        return true;
    } else { //Login was not successful.
        //Authentication Failed.
        cout << "authentication failed \n";
        conn.writeToSocket_user(usr);
        std::string temp;
        conn.readFromSocket(temp); //CONTINUE INSTR
        std::string rejected( LOGIN_REJECTED );
        conn.writeToSocket(rejected);
        return false;
    }
}

bool Server::handleLogout() {
    //Forget user details.
    this->user.userID = "";
    this->user.clientDirectory = "";
    this->user.password = "";
    this->user.serverDirectory = "";
    return true;
    //Done.
}

#endif
