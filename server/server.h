#ifndef SERVER_H
	#define SERVER_H
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include "arpa/inet.h"
#include <unordered_map>
#include <poll.h>
#include <fstream>
typedef int Socket ; //Because safer.


struct userdetails {
	std::string userID;
	std::string password;
	std::string serverDirectory;
	std::string clientDirectory;
};
class Server{
private:

	struct userdetails user;
	int port;
	int n, clientLength;
	std::string tempPW;
	unordered_map< std::string , struct userdetails > userDetails;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	char clienturl[CL_URL_LEN];
	Socket ssock;
	Socket csock;	
	std::string activeUserID;
	void startServer(); //Initializes serverAddr.
	void readDatabase();
	void getClient(); //Infinite loop for the main process to keep accepting new processes,

	void handleClient(Socket& csock); // Every individual client is handled here.
	
	void getInstruction(std::string& inst , Socket& csock); //Reads into the inst file.
	void handleInstruction(std::string& inst); //Handles inputs that come in from the socket.
		//List of instructions
		bool mainPing(); 
			
		bool chat(); // Infinite chat
			void readMsg(std::string& p);
			void writeMsg(std::string& p);
		
		void mainRegisterUser();
		void mainAuthenticateUser();
		void mainFileToServer();
			bool getFileNameFromClient(char* buffer);
			bool readFileFromClient(char* buffer);
		void mainFileToClient();

		bool authenticateUser(std::string& output); //Authentitcates using userID and password given by client. Also takes in Directory stuff. Sets the user details.
		bool registerUser( std::string& output ); //Other options too.	
		bool checkPassword( std::string pw );
		bool checkUsername( std::string& uID );


		bool fileToServer( std::string& filename , Socket& csock ); //Transfers fileToServer 
		bool fileToClient( std::string& filename , Socket& csock );

public:
	Server(int nClients);
	~Server();
	void error(std::string s);
};

//Utility function
void Server::error(string s) {
	std::cout << s << "\n";
}

#endif