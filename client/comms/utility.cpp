#ifndef UTILITY_CPP
	#define UTILITY_CPP
#include <poll.h>

bool readFromSocket( Socket& csock , char* buffer , int buffer_size) {
	memset( buffer , 0 ,buffer_size);
	struct pollfd ready;
		ready.fd = csock;
		ready.events = POLLIN;

	int rv = poll( &ready , 1, POLL_TIMEOUT);
	if ( rv < 0 ) {
		printf("Failed to event read ... < POLLIN Event in getInstruction() > \n");
		return false;
	} else if ( rv == 0 ) {
		printf("Time out... on address from... \n" );
		return false;
	} else {
		//Read here.
		if ( ready.revents & POLLIN ) {
			rv = read( &csock , buffer , buffer_size);
			if ( rv < 0 ) {
				printf("failed to read from buffer.. \n");
					return false;
			} else {
				return true;
			}
		}
	}
	//Assert : Read to buffer completed.
}

//write a char[] onto the csock
bool writeToSocket( Socket& csock , char* buffer , int buffer_size) {
	struct pollfd ready;
		ready.fd = csock;
		ready.event = POLLOUT;
	int rv = poll( &ready , 1 , POLL_TIMEOUT);
	if ( rv < 0 ) {
		printf("Failed to event read ... < POLLOUT Event in getInstruction() > \n");
		return false;
	} else if ( rv == 0 ) {
		printf("Time out... on address from... \n" );
		return false;
	} else {
		//Read here.
		if ( ready.revents & POLLOUT ) {
			rv = write( &csock , buffer , buffer_size);
			if ( rv < 0 ) {
				printf("failed to write from buffer.. \n");
					return false;
			} else {
				return true;
			}
		}
	}
}

//Write a string into the csock
bool writeToSocket( Socket& csock , std::string buffer , int buffer_size = -1 ) {
	struct pollfd ready;
		ready.fd = csock;
		ready.event = POLLOUT;
	int rv = poll( &ready , 1 , POLL_TIMEOUT);
	if ( rv < 0 ) {
		printf("Failed to event read ... < POLLOUT Event in getInstruction() > \n");
		return false;
	} else if ( rv == 0 ) {
		printf("Time out... on address from... \n" );
		return false;
	} else {
		//Read here.
		if ( ready.revents & POLLOUT ) {

			if ( buffer_size > 0 ) {
				rv = write( &csock , buffer.c_str() , buffer_size);
			} else {
				rv = write( &csock , buffer.c_str() , buffer.size());
			}
			if ( rv < 0 ) {
				printf("failed to write from buffer.. \n");
					return false;
			} else {
				return true;
			}
		}
	}
}

#endif