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
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    UserDetails newuser;
    conn.readFromSocket_user( newuser );
    UserDetails temp = newuser;
    if ( !fetchUserbyID( temp ) ) { //A user with that ID doesn't exist.
        return false;
    } else { //A user with that ID doesnt exist
        this->createNewUser( newuser );
        return true;
    }
}

bool Server::createNewUser( UserDetails& newuser ) {
    /*
     * TODO : Add it to user database
     *Create Directory for him on the server side.
    */
    this->AddUser(newuser.userID, newuser.password, newuser.serverDirectory, newuser.clientDirectory); //Added to database.
    this->createUserDirectory( newuser );
    return true;
}


#endif
