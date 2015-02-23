#include <poll.h>

bool Server::handlePing() {
	//Assert : This is called AFTER the REQUEST_PING has been read.
    return conn.writeToSocket( PING_ACCEPTED );
	
}
