#ifndef CLIENT_PING_CPP
#define CLIENT_PING_CPP
#include "client.h"
#include "../../common/instructions.h"
#include "../../common/communications.h" //does typedef int Socket.
#include <QMessageBox>
bool Client::handlePing() { //Handles the entire ping
    std::string temp(PING_REQUEST);
    std::string acceptance(PING_ACCEPTED);
    if ( conn.writeToSocket(temp)) { //Sends the ping
        temp = "";
        bool rv = conn.readFromSocket(temp); //Receives the ping
        if (rv ) {
            if( temp == acceptance ) {
                return true;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}
#endif
