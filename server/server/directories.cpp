#ifndef DIRECTORIES_CPP
#define DIRECTORIES_CPP

#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
#include <boost/filesystem.hpp>

bool Server::createUserDirectory( UserDetails& usr ) {
    cout << " creating directory for " << usr.userID << "\n";
    string mystr = SERVER_DIRECTORY; //  includes the '/' character at the end of it.
    mystr += usr.userID; //Unique location for all.
    cout << "directory is : " << mystr << "\n";
    boost::filesystem::path directory(mystr.c_str() );
    int status = boost::filesystem::create_directories(directory);// , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //Hopefully, it works recursively.
    if(status == 0){
        cout<<"Directory created\n";
        return true;
    }else{
        cout<<"Not Created\n";
        return false;
    }
}

bool Server::makeAdminDirectory() {
    return false;
}

#endif
