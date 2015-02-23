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


bool readFromSocket( Socket& csock , std::string& reply) {
	
	char buffer[INSTR_BUF_SIZE];

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
				string temp(buffer);
				reply = temp;
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

bool writeToSocket ( Socket& csock , vector<string>& vec ) {
	// Informative Buffer size = 254 , Information buffer = @254
	char beginBuffer[INSTR_BUF_SIZE];
		memset( beginBuffer , 0, INSTR_BUF_SIZE);
		beginBuffer[0] = 'X';
		beginBuffer[INSTR_BUF_SIZE-1] = '0';

	//Beginning of message
	writeToSocket( csock , beginBuffer , INSTR_BUF_SIZE);
	string reply;
	readFromSocket(csock , reply);
	if ( reply == INF_READY ) {
		//read stuff.
	} else {
		#ifdef SERVER_SIDE
			printf( " other end was not ready to read stuff ... \n");
		#endif
		return false;
	}

	//Writing vector of strings
	int vecsize = vec.size();
	for(int i = 0; i< vecsize ; ++i) { //Write every individual string.
		if( vec[i].size() > 254 ) {
			#ifdef SERVER_SIDE
				printf(" asked to write a string too big\n");
			#endif
			return false;
		} else {

			//Valid string to write into buffer.
			string replymsg;
			// Generate message
			char msg[INSTR_BUF_SIZE];
				memset(msg , 0 , INSTR_BUF_SIZE);
				for(int i=0; i< vec[i].size(); ++i) {
					msg[i] = vec[i];
				}
				msg[INSTR_BUF_SIZE-1] = '1';

			writeToSocket(csock , msg , INSTR_BUF_SIZE);
			//Other end should reply 
			readFromSocket( csock , replymsg);
			if (replymsg == INF_READY) {
				
			} else {
				#ifdef SERVER_SIDE
					printf( " other end was not ready to read stuff ... \n");
				#endif
				return false;	
			}

		}
	} //Assert message has been written.
	readFromSocket(csock , reply);
	if ( reply == INF_READY ) {
		//End of message instruction
		char endBuffer[INSTR_BUF_SIZE];
		memset( endBuffer , 0 , INSTR_BUF_SIZE);
			endBuffer[0] = 'X';
			endBuffer[INSTR_BUF_SIZE-1] = '0';
		writeToSocket( csock , endBuffer , INSTR_BUF_SIZE);
		return true;
	} else {
		#ifdef SERVER_SIDE
			printf( " other end was not ready to read stuff ... \n");
		#endif
		return false;
	}
}

bool readFromSocket( Socket& csock , vector<string>& vec ) {
	char initiationBuffer[INSTR_BUF_SIZE];
		memset(initiationBuffer , 0, INSTR_BUF_SIZE);
	readFromSocket( csock , initiationBuffer , INSTR_BUF_SIZE);
	if ( (initiationBuffer[ 0 ]=='X') && (initiationBuffer[ INSTR_BUF_SIZE - 1 ]=='0') ) {
		//begin
		//continue really.
	} else {
		#ifdef SERVER_SIDE
			printf(" the other side aint doing this \n");
		#endif
		return false;
	}

	bool cont = true;
	//Into loop.
	while( cont ) {
		//Read the message and put it into the vector.
		char msg[INSTR_BUF_SIZE];
			memset(msg , 0, INSTR_BUF_SIZE);
		readFromSocket(csock , msg , INSTR_BUF_SIZE);
		writeToSocket(csock , INF_READY);
		
		cont = ((msg[INSTR_BUF_SIZE-1] == '1') && ( msg[0] == 'X'));

		string message(msg);
		if ( message.size() < INSTR_BUF_SIZE-1) {
			//Nothing to do.
		} else {
			msg[INSTR_BUF_SIZE-1] = 0;
			string temp(msg);
			message = tmp;
		}
		vec.push_back(message);		
	}


}
 
#endif