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
#include <QtSql/QtSql>

//Other stuff.
#include <vector>
#include <unordered_map>
#include <poll.h>
#include <fstream>

//QtSql stuff
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QSqlError>

#include "serverdefinitions.h"
#include "../../common/instructions.h" //must have.
#include "../../common/communications.h" //another must have.


class Server{
private:

    struct UserDetails user;
	int port;
    int clientLength;
	std::string tempPW;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
    char clienturl[CLIENT_URL_LEN];
	Socket ssock;
	Socket csock;	
    Communications conn; //In true SQL style. Created in getClient() function for child process.
    QSqlDatabase db; //Database.
    unordered_map< std::string , UserDetails > userDetails; //Effectively part of the class Server. Kept outside because sqlite3

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
        bool SyncControllerShared( string uID );


        bool removeFile( string filename);//removal.cpp



        //database.cpp :
        bool CreateTable(); //database.cpp
        bool CreateTable( string& s );
        bool CreateTableuser();
        bool SyncController( string uID );
        bool Createtableshared();
        bool fetchUserbyID( UserDetails& usr ); //Returns false is no such user is present
        bool main_CreateDatabase(); //db.cpp
        int  CheckifFileExists(string finame , string owner);
        bool main_AddUser(string uID, string Password, string Server_Dir, string Client_Dir);
        bool main_DeleteUser(string uID);
        bool UpdateDatabase(std::string uid, std::string pwd); //database.cpp
        bool main_ReadDatabase(); //database.cpp
        bool main_getAdmin();//database.cpp
        bool AddFile(string finame, int version , string owner);
        bool updateDatabase(UserDetails user, EDIT_MODE mode);//database.cpp
        //int callback(void *NotUsed, int argc, char **argv, char **azColName);//database.cpp
        //bool CreateTable();
        bool AddUser(string uID, string Password, string Server_Dir, string Client_Dir);
        bool DeleteUser(string uID);
        bool main_CreateDictionary();

        //static int CreateHashTable(void *NotUsed, int argc, char **argv, char **azColName);//database.cpp

        bool authenticate(std::string userid, std::string passwd); // Takes userId, password as plain strings and compares against database.
        bool authenticate(UserDetails& usr);
        bool createNewUser( UserDetails& usr ); //register.cpp

        //upload.cpp
        bool getFilestream( std::fstream& reader , std::string& _filename);
        std::string processFileName( std::string filename);//Decides where the filename has to go.
        bool createUserDirectory( UserDetails& usr); //directories.cpp
        bool makeAdminDirectory(); //directories.cpp

public:
    Server();
	~Server();
};
#endif
