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
#include "../../common/instructions.h" //must have.
#include "../../common/communications.h" //another must have.
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
    Communications conn; //In true SQL style. Created in getClient() function for child process.

    //Starting it up. server.cpp
	void startServer(); //Initializes serverAddr.
	void getClient(); //Infinite loop for the main process to keep accepting new processes,
    void handleClient(); // Every individual client is handled here.
    bool getInstruction(std::string& inst); //Reads into the inst file.
    bool handleInstruction(std::string& inst); //Handles inputs that come in from the socket.
        //List of instructions and their handlers.
        bool handlePing(); //ping.cpp
        bool handleRegistration(); //registration.cpp
        bool handleLogin(); //login.cpp
        bool handleLogout(); //login.cpp
        bool handleUpload(); //upload.cpp
        bool handleDownload(); //download.cpp
        bool handleRemoveFile(); //removal.cpp
        bool handleSync(); //sync.cpp
        bool handleRevert(); //revert.cpp
        bool handleShare(); //share.cpp
        bool handleUnshare(); //share.cpp
		
        //removal.cpp
        bool removeFile( string filename, string dir);

        //database.cpp :
        bool fetchUserbyID( UserDetails& usr ); //Returns false is no such user is present
        bool main_CreateDatabase(); //db.cpp
        bool main_CreateTable();
        bool main_AddUser(string uID, string Password, string Server_Dir, string Client_Dir);
        bool main_DeleteUser(string uID);
        bool main_ReadDatabase(); //database.cpp
        bool main_getAdmin();//database.cpp
        bool main_ReadUsers();//database.cpp
        bool updateDatabase(UserDetails user, EDIT_MODE mode);//database.cpp
        bool authenticate(std::string userid, std::string passwd); // Takes userId, password as plain strings and compares against database.
        bool createNewUser( UserDetails& usr ); //register.cpp

        bool createUserDirectory( userDetails& usr); //directories.cpp
        bool makeAdminDirectory(); //directories.cpp
public:
    Server();
	~Server();
};
#endif
