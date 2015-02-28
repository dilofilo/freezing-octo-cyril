#ifndef SYNC_CPP
#define SYNC_CPP

#include "server.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
 #include <boost/filesystem.hpp>


bool Server::handleSync() {

    SyncController( user.userID );
    // A file named log.txt shoul've been created
    // The file is sent to the client
    string filename = user.userID + "log.txt"; //Slightly more unique name.
    this->SyncController(user.userID);
    conn.writeToSocket_file(filename); //All files that the user has access to and owns.
    // Remove log.txt


    string cont;
    conn.readFromSocket( cont );    // Reading a continue.
    this->SyncControllerShared(user.userID);
    conn.writeToSocket_file(filename); //All the files that the uses has access to but doesnt own.

    boost::filesystem::remove(filename);
    return true; //Then, the client sends apt upload and download requests.
}

#endif
