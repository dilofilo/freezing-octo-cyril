#ifndef SERVER_CPP
	#define SERVER_CPP

#include "server.h"
#include "ping.cpp"
#include "authenticate.cpp"
#include "register.cpp"
#include "instructions.h"

Server::Server(int n) {
	//Initialize number of clients
	activeUserID = "";
	n = 0;
	startServer();
}

Server::~Server() {
	//Close windows. Close all connections etc.
}


void Server::startServer() {
	
	//Initialize server-only things.
	readDatabase();
	ssock = socket(AF_INET, SOCK_STREAM, 0); //Server's half of the socket.
	if ( ssock < 0 ) {
		//Connection failed.
        printf(" host socket creation failed...exitting. please ensure that the appropriate ports are open. \n");
        exit(1);
    } else {
        printf(" host socket created... \n");
	}
	memset( &serverAddr , 0 , sizeof(serverAddr));
 	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_addr.s_addr = INADDR_ANY;  
	serverAddr.sin_port = PORT;

	if ( bind( ssock , (struct sockaddr * ) &serverAddr , sizeof(serverAddr)) < 0 ) {
        printf(" socket binding failed... \n");
		exit(1);
	} else {
        printf(" socket successfully binded... \n");
	}	
	//Assert : ssock is now ready - there is one incoming connection.
	getClient();	
}

void Server::handleClient() {
	bool socketAlive = true;
	string instruction;
	while ( socketAlive ) {
		instruction = "";
        getInstruction(instruction);
		handleInstruction(instruction); //Takes it to closing.
	}
	close(csock);
	return;
}

void Server::handleInstruction(std::string& instr)
{
    if ( instr ==  PING_REQUEST) {
        handlePing();
    }

}


#define FILE_BUF_SIZE 255
void Server::mainFileToServer()
{
		bool cont =true;
		while(cont)
		{
			char buffer[FILE_BUF_SIZE];
			getFileName(buffer);
			readFile(buffer);
     	}
}

bool Server::getFileName(char * buffer) {
	//Read from csock.
}
void Server::mainFileToClient() {

}




void Server::getClient() {
	listen( ssock , MAX_CONNECTION_REQUESTS ); // Back log of 10.
	//Assert : ssock is now ready - there is one incoming connection.
	pid_t cpid;
	while(true) {
		clientLength = sizeof(clientAddr);
		csock = accept( ssock , (struct sockaddr*) &clientAddr , (socklen_t*) &clientLength);
		if (csock<0) {
			cout << " error accepting connection... \n";
			exit(1);
		}  else {
			cout << " connection accepted... \n";
		}

		inet_ntop( AF_INET, &(clientAddr.sin_addr) , clienturl , CL_URL_LEN );
		
		//Create a child ID.
		cpid = fork(); //fork returns 0 to child and process id to forker.
		if ( cpid == 0 ) {
			//Child ID does work.
			//Original ID continues to listen for connections.
			close(ssock);
            handleClient();
		} else {
			close(csock);
		}
	}
	close(ssock);
}



void Server::getInstruction( std::string& inst ) {
    inst = "";
    return conn.readFromSocket( inst );
}
#endif
