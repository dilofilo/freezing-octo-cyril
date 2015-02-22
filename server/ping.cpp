#include <poll.h>
bool Server::returnPing() {
	std::string p,q;

	while(true) {
		readMsg(p);
		writeMsg(q);
	}
}

void Server::readMsg(std::string& p) {
	struct pollfd polledSock;
		polledSock.fd = csock;
		polledSock.events = POLLIN;

	int rv = poll( &polledSock , 1 , POLL_TIMEOUT);
	if ( rv < 0 ) {
		printf("Failed to event read ... < POLLIN Event in getInstruction() > \n");
		exit(1);
	} else if ( rv == 0 ) {
		printf("Time out... on address from... \n" );
	} else {
		//Read instruction
		if (polledSock.revents & POLLIN) {
			char instBuffer[255];
			int readSize = read( csock , instBuffer , 255);
			if ( readSize < 0 ) {
				printf(" weird reading error ... from readValue... getInstruction()  \n");
				exit(1);
			} else {
				std::string tempString;
					tempString.assign(instBuffer , 255);
				p = tempString;
			}
		}
	}
	return;
}

void Server::writeMsg(std::string& p) {
	struct pollfd polledSock;
		polledSock.fd = csock;
		polledSock.events = POLLOUT;
	int rv = poll( &polledSock , 1 , POLL_TIMEOUT);
	if ( polledSock.revents & POLLOUT) {
		int wmsg = write(csock , p.c_str() , p.size());
	}
	return;
}