#ifndef REGISTRATION_CPP
#define REGISTRATION_CPP

#include "server.h"
#include "../../common/instructions.h"
#include "serverdefinitions.h"
#include "../../common/communications.h"

bool Server::handleRegistration() {

    /*
     * Assert : Instruction for registration has been read.
     *Write continue.
     * Read the struct.
    */
    cout << "read a reg_request . now writing continue\n";
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    UserDetails newuser;
    conn.readFromSocket_user( newuser );
    cout << " registration details : \n id=" << newuser.userID << "\npwd=" << newuser.password << "\nclidir=" << newuser.clientDirectory << "\n";
    UserDetails temp = newuser;
    if ( !fetchUserbyID( temp ) ) { //A user with that ID exists
        cout << "registration rejected \n";
        string reply = REGISTRATION_REJECTED;
        conn.writeToSocket(reply);
        return false;
    } else { //A user with that ID doesnt exist
        this->createNewUser( newuser );
        cout << "registration accepted\n";
        string reply = REGISTRATION_ACCEPTED;
        conn.writeToSocket(reply);
        return true;
    }
}

bool Server::createNewUser( UserDetails& newuser ) {
    /*
     * TODO : Add it to user database
     *Create Directory for him on the server side.
    */
    cout << "new user to be created \n";
    this->AddUser(newuser.userID, newuser.password, newuser.serverDirectory, newuser.clientDirectory); //Added to database.
    this->createUserDirectory( newuser );
    return true;
}


#endif
