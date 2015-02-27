#ifndef SYNC_CPP
#define SYNC_CPP

#include "server.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"


bool Server::handleSync() {

    SyncController( user.userID );
    // A file named log.txt shoul've been created
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);

    // The user should ask the server to download log.txt

    return true;
}

#endif
