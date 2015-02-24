#ifndef USERDATABASE_CPP
#define USERDATABASE_CPP
/*
This file handles with reading databases and reading user's file directory etc.

TODO list.
*/

#include "server.h"

bool Server::updateDatabase(UserDetails user , EDIT_MODE mode) {
    return false;
}


bool Server::main_ReadDatabase() { //The structure of the reading.
    if( main_GetAdmin() ) {
        if (main_ReadUsers()) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Server::main_GetAdmin() { //Modify this function accordingly.
    return true;
}
bool Server::main_ReadUsers() { //Modify this function accordingly.
    return true;
}

bool Server::authenticate(std::string userid , std::string passwd) {
    return false;
}

#endif
