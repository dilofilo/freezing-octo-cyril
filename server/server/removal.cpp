#ifndef REMOVAL_CPP
#define REMOVAL_CPP

#include "server.h"
#include <string>
#include <stdio.h>
#include "serverdefinitions.h"
bool Server::handleRemoveFile(){
    //Assert : Given command to REMOVE FILE.
    //Tell it to continue, then read the file name.
    string cont(CONTINUE);
    conn.writeToSocket(cont);
    string f;
    conn.readFromSocket(f);
    return removeFile(f);
}
bool Server::removeFile(string filename) {
    string newfilename = SERVER_DIRECTORY + user.userID + "/" + filename;
    if(remove(newfilename.c_str()) == 0){
        cout<<"File Deleted Successfully."<<"\n";
        return true;
    }else{
        cout<<"File Not Deleted."<< "\n";
        return false;
    }
}

#endif
