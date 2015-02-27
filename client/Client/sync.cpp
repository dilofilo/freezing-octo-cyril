#ifndef SYNC_CPP
#define SYNC_CPP
#include "client.h"

bool Client::handleSync() {
    string syncreq(SYNC_REQUEST);
    conn.writeToSocket(syncreq); //Write sync request
    string cont; //continues.
    conn.readFromSocket(cont);
    return true;

}

#endif
