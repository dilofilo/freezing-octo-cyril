#ifndef SERVER_CPP
	#define SERVER_CPP

#include "../../common/instructions.h"
#include "../../common/communications.h"
#include "server.h"
#include "ping.cpp"
#include "database.cpp"
#include "login.cpp"
#include "upload.cpp"
#include "download.cpp"
#include "removal.cpp"

Server::Server() {
	//Initialize number of clients
    user.userID = "";
    user.password = "";
    user.clientDirectory = "";
    user.serverDirectory = "";
	startServer();
}

Server::~Server() {
	//Close windows. Close all connections etc.
}


void Server::startServer() {
	
	//Initialize server-only things.
    main_CreateDatabase();
    main_CreateDictionary();
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

        inet_ntop( AF_INET, &(clientAddr.sin_addr) , clienturl , CLIENT_URL_LEN );
		
		//Create a child ID.
		cpid = fork(); //fork returns 0 to child and process id to forker.
		if ( cpid == 0 ) {
			//Child ID does work.
			//Original ID continues to listen for connections.
            close(ssock);
            conn.setSocket(csock); //Created.
            handleClient();
		} else {
			close(csock);
		}
	}
	close(ssock);
}


void Server::handleClient() {
    bool socketAlive = true;
    string instruction = "";
    while ( socketAlive ) {
        if ( getInstruction(instruction) ) { //Also sets instruction = ""
            if (handleInstruction(instruction) ) { //Returns if the handler was succesful, take appropriate action.
            } else {
                #ifdef SERVER_SIDE
                printf( " handle instruction failed .. \n");
                #endif

            }
        } else {
            #ifdef SERVER_SIDE
            printf( " get instruction failed .. \n");
            #endif
        }
    }
    close(csock);
    return;
}

bool Server::getInstruction( std::string& inst ) {
    inst = "";
    printf( " waiting for instructions \n");
    return conn.readFromSocket( inst );
}

bool Server::handleInstruction(std::string& instr) {
    cout << "handling : " << instr << "\n";
    if ( instr ==  PING_REQUEST) {//Why am I able to convert a const char[] to a string?
        return handlePing();
    }else if( instr == REGISTRATION_REQUEST ) {
        return handleRegistration();
    }else if( instr == LOGIN_REQUEST ){
        return handleLogin();
    }else if( instr == LOGOUT ){
        return handleLogout();
    }else if( instr == C_TO_S_FILE ){ //File upload ( to server )
        return handleUpload();
    }else if( instr == S_TO_C_FILE ){ //File download (from server)
        return handleDownload();
    }else if( instr == REMOVE_REQUEST ){ //Remove File from Server - and all its databses.
        return handleRemoveFile();
    }else if( instr == SYNC_REQUEST ){ //
        return handleSync();
    }else if( instr == REVERT_REQUEST ){
        return handleRevert();
    }else if( instr == SHARE_REQUEST ){
        return handleShare();
    }else if( instr == UNSHARE_REQUEST ){
        return handleUnshare();
    }else if ( instr == EXIT_REQUEST ){
        ::close(csock);
        return true;
    }else {
        return false;
    }
}


#endif
