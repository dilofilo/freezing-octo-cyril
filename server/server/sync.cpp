#ifndef SYNC_CPP
#define SYNC_CPP

#include "server.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
 #include <boost/filesystem.hpp>


bool Server::handleSync( string uid ) {

    SyncController( user.userID );
    // A file named log.txt shoul've been created
    // The file is sent to the client
    string filename = uid + "log.txt"; //Slightly more unique name.
    cout << user.userID << "\n";
    this->SyncController(uid);
    cout << "prepareing to write log.txt \n";
    conn.writeToSocket_file(filename); //All files that the user has access to and owns.
    // Remove log.txt
    cout << "wrote log.txt \n";
    boost::filesystem::remove(filename);


    string cont;
    conn.readFromSocket( cont );    // Reading a continue.
    this->SyncControllerShared(uid);
    cout << " writing loglt.xt \n";
    conn.writeToSocket_file(filename); //All the files that the uses has access to but doesnt own.
    cout << "wrote log.txt \n";
    boost::filesystem::remove(filename);
    return true; //Then, the client sends apt upload and download requests.
}

#endif
