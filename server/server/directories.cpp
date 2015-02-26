#ifndef DIRECTORIES_CPP
#define DIRECTORIES_CPP

#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
#include <sys/stat.h>

bool Server::createUserDirectory( UserDetails& usr ) {

    string mystr = SERVER_DIRECTORY;
    int status = mkdir( mystr.c_str() , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);


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
