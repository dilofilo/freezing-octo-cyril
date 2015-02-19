#ifndef SERVER_H
	#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include "arpa/inet.h"

typedef int Socket ; //Because safer.
#define PORT 5000
#define MAX_CONNECTION_REQUESTS 10
#define POLL_TIMEOUT 15000
struct userdetails {
	string userID;
	string serverDirectory;
	string clientDirectory;

};
class Server{
private:

	struct userdetails user;
	int port;
	int n, clientLength;

	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	Socket ssock;
	Socket csock;	
	string activeUserID;
	
	void startServer(); //Initializes serverAddr.
	void getClient(); //Infinite loop for the main process to keep accepting new processes,

	void handleClient(); // Every individual client is handled here.
	
	void getInstruction(string& inst); //Reads into the inst file.
	void handleInstruction(string& inst); //Handles inputs that come in from the socket.
		//List of instructions
		bool returnPing(); // Ping and pingback.

		bool authenticateUser(string& userID , string& pw , string& output); //Authentitcates using userID and password given by client. Also takes in Directory stuff. Sets the user details.
		bool registerUser(string& userID , string& pw , string& output); //Other options too.	

		bool fileToServer( string& filename , Socket& csock ); //Transfers fileToServer 
		bool fileToClient( string& filename , Socket& csock );

public:
	Server(int nClients);
	~Server();

};
#endif