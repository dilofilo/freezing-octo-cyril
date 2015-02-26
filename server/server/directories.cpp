#ifndef DIRECTORIES_CPP
#define DIRECTORIES_CPP

#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
#include <sys/stat.h>

bool Server::createUserDirectory( UserDetails& usr ) {

    string mystr = SERVER_DIRECTORY; //  includes the '/' character at the end of it.
    mystr += usr.userID; //Unique location for all.
    int status = mkdir( mystr.c_str() , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //Hopefully, it works recursively.
    if(status == 0){
        cout<<"Directory created"<<endl;
        return true;
    }else{
        cout<<"Not Created"<<endl;
        return false;
    }
}

bool Server::makeAdminDirectory() {
    return false;
}

#endif
