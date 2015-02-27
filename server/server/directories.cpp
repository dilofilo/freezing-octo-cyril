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

    for ( int i =1;i<MAX_VERSIONS; i++){
        string foo = to_string(i);
        string mystr = SERVER_DIRECTORY + usr.userID + "/v_" + foo;
        boost::filesystem::path newpath(  mystr.c_str() );
        status = boost::filesystem::create_directories(newpath);
    }
    cout << "all directories created \n";
    return true;
}

bool Server::makeAdminDirectory() {
    return false;
}

#endif
