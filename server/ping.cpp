#include <poll.h>

bool Server::mainPing() {
	//Assert : This is called AFTER the REQUEST_PING has been read.
	if ( writeToSocket(csock , ACCEPT_PING) ) {
		printf(" ping successful \n");
		return true;
	} else {
		printf(" ping not successful \n");
		return false;
	}
	
}