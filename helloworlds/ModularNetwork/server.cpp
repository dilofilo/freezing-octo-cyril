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
		cout << " Socket creation failed \n";
		exit(1);
	} else {
		cout << " host socket created... \n";
	}
	memset( &serverAddr , 0 , sizeof(serverAddr));
 	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_addr.s_addr = INADDR_ANY;  
	serverAddr.sin_port = PORT;

	if ( bind( ssock , (struct sockaddr * ) &serverAddr , sizeof(serverAddr)) < 0 ) {
		cout << " binding failed... \n";
		exit(1);
	} else {
		cout << " successfully binded... \n";
	}

	
	//Assert : ssock is now ready - there is one incoming connection.
	getClient();
	
}

void Server::readDatabase() 
{
	std::ifstream f;
	f.open("details.txt");

	while(!f.eof())
	{
		userdetails temp;
		
		f>>temp.userID;
		f>>temp.password;
		f>>temp.serverDirectory;
		f>>temp.clientDirectory;
		std::pair< std::string , userdetails > temppair( temp.userID , temp);

		userDetails.insert(temppair);

	}

}
void Server::handleClient( Socket& csock ) {
	bool socketAlive = true;
	string instruction;
	while ( socketAlive ) {
		instruction = "";
		getInstruction(instruction , csock);
		handleInstruction(instruction); //Takes it to closing.
	}
	close(csock);
	return;
}

void Server::handleInstruction(std::string& ins)
{
	switch (instr)
	{		
		case AUTH : {
			mainAuthenticateUser();
			break;
		}
		case REG : {
			mainRegisterUser();
			break;
		}
		case GETFILE : {
			mainFileToServer();
			break;
		}
			
		case RETFILE : {
			mainFileToClient();
			break;
		}
		default : {

		}

	}
}

void mainFileToServer()
{


}





void Server::getClient() {
	listen( ssock , MAX_CONNECTION_REQUESTS ); // Back log of 10.
	//Assert : ssock is now ready - there is one incoming connection.
	pid_t cpid;
	while(true) {
		clientLength = sizeof(clientAddr);
		csock = accept( ssock , (struct sockaddr *) clientAddr , (socklen_t*) clientLength);
		if (csock<0) {
			cout << " error accepting connection... \n";
			exit(1);
		}  else {
			cout << " connection accepted... \n";
		}

		inet_ntop( AF_INET, &(clientAddr.sin_) , clientAddr , CLADDR_LEN );
		
		//Create a child ID.
		cpid = fork(); //fork returns 0 to child and process id to forker.
		if ( cpid == 0 ) {
			//Child ID does work.
			//Original ID continues to listen for connections.
			close(ssock);
			handleClient( csock );
		} else {
			close(csock);
		}
	}
	close(ssock);
}



void Server::getInstruction( std::string& inst , Socket& csock) {
	struct pollfd polledSock;
		polledSock.fd = csock;
		polledSock.events = POLLIN;

	int rv = poll( polledSock , 1 , POLL_TIMEOUT);
	if ( rv < 0 ) {
		cout << "Failed to event read ... < POLLIN Event in getInstruction() >" << clientAddr << "\n ";
		exit(1);
	} else if ( rv == 0 ) {
		std::cout << "Time out... on address from...\n";
	} else {
		//Read instruction
		if (polledSock.revents & POLLIN) {
			char instBuffer[255];
			int readSize = read( csock , instBuffer , 255);
			if ( readSize < 0 ) {
				std::cout << " weird reading error ... from readValue... getInstruction() \n";
				exit(1);
			} else {
				std::string tempString( instBuffer );
				inst = tempString;
			}
		}
	}
}
#endif