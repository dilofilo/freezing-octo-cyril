#ifndef PING_CPP
#define PING_CPP
#include <poll.h>
#include <iostream>
#include "server.h"

bool Server::handlePing() {
	//Assert : This is called AFTER the REQUEST_PING has been read.
    string temp(PING_ACCEPTED);

    bool rv = conn.writeToSocket( temp );
    if ( rv )  {
        cout << temp << " was written onto socket \n";
        printf("ping was successful \n");
    }
    return rv;
}
#endif
