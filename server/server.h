#ifndef SERVER_H
	#define SERVER_H
using namespace std;

//Connectivity stuff
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
#include "arpa/inet.h"

//Other stuff.
#include <vector>
#include <unordered_map>
#include <poll.h>
#include <fstream>

#include "serverdefinitions.h"
#include "../common/instructions.h" //must have.
#include "../common/communications.h" //another must have.
class Server{
private:

    struct UserDetails user;
	int port;
    int clientLength;
	std::string tempPW;
    unordered_map< std::string , struct UserDetails > userDetails;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
    char clienturl[CLIENT_URL_LEN];
	Socket ssock;
	Socket csock;	
	std::string activeUserID;
    Communications conn; //In true SQL style. Created in getClient() function for child process.

	void startServer(); //Initializes serverAddr.
    bool main_ReadDatabase();
    bool main_GetAdmin();
    bool main_ReadUsers();

	void getClient(); //Infinite loop for the main process to keep accepting new processes,

    void handleClient(); // Every individual client is handled here.
	
    bool getInstruction(std::string& inst); //Reads into the inst file.
    bool handleInstruction(std::string& inst); //Handles inputs that come in from the socket.
		//List of instructions
        bool handlePing();
			
		
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
    Server();
	~Server();
};
#endif
