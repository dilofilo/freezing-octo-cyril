#ifndef REMOVAL_CPP
#define REMOVAL_CPP

#include <stdio.h>

bool Server::removeFile(string filename, string directory){

    string newfilename = directory + filename;
    if(remove(newfilename.c_str()) == 0){
        cout<<"File Deleted Successfully."<<endl;
        return true;
    }else{
        cout<<"File Not Deleted."<<endl;
        return false;
    }

}

#endif
