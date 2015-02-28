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


SSL_CTX* InitServerCTX(void) {
    SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();		/* load & register all cryptos, etc. */
    SSL_load_error_strings();			/* load all error messages */
    SSL_library_init();

    method = const_cast<SSL_METHOD*>(SSLv3_server_method());		/* create new server-method instance */
    ctx = SSL_CTX_new(method);			/* create new context from method */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}
void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);	/* Get certificates (if available) */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}
void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

Server::Server() {
	//Initialize number of clients
    user.userID = "";
    user.password = "";
    user.clientDirectory = "";
    user.serverDirectory = "";
    serverCTX = InitServerCTX(); //Get a new ctx.
    LoadCertificates(serverCTX , "mycert.pem" , "mycert.pem");
    startServer();
}

Server::~Server() {
	//Close windows. Close all connections etc.
    SSL_CTX_free(serverCTX);
}


void Server::startServer() { //Gets
	
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
    //ssock is now ready.
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
            cout << " let me check error accepting connection... \n";
			exit(1);
		}  else {
			cout << " connection accepted... \n";
		}

        inet_ntop( AF_INET, &(clientAddr.sin_addr) , clienturl , CLIENT_URL_LEN );
        //SSL stuff
        sslsock = SSL_new(serverCTX); //makes the new socket.
        SSL_set_fd(sslsock , csock);
        conn.setSocket(csock , sslsock); //Created. - copies code elsewhere
        if ( SSL_accept(sslsock) == -1 ) {
            printf("SSL ACCEPT FAILED\n");
        } else {
            printf("SSL ACCEPTED \n");
        }
        ShowCerts(sslsock);

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

    close(csock);
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
