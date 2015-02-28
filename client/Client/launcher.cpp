#ifndef LAUNCHER_CPP
#define LAUNCHER_CPP

#include "client.h"
/*---------------------------------------------------------------------*/
SSL_CTX* InitCTX(void)
{

    SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();		/* Load cryptos, et.al. */
    SSL_load_error_strings();			/* Bring in and register error messages */
    SSL_library_init();

    method = (const_cast <SSL_METHOD*> (SSLv3_client_method()));		/* Create new client-method instance */
    ctx = SSL_CTX_new(method);			/* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
} //InitCTX
/*---------------------------------------------------------------------*/
void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);	/* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);							/* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);							/* free the malloc'ed string */
        X509_free(cert);					/* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}


void Client::launch() {
    std::string serverip = ((this->ui->txt_serverip)->text()).toUtf8().constData(); //Gets the IP address of the user.
    QMessageBox msgBox;

    if ( this->prepareSocket(serverip) ) {
        //Get the socket and set it for all of its kids.
        //Create the login screen and give it the socket.

        if (this->createPages()) { //Creates the LOGIN PAGE here.
            this->showLoginPage(); // Shows the LOGIN PAGE here.
        } else {
            msgBox.setText(" can't open the login page. Dont ask me please.");
            msgBox.exec();
        }
    } else {
        //TODO: prepareSocket failed.
        msgBox.setText("Connection unsuccessful! Please check your IP Addresses and make sure that the appropriate PORT is open.");
        msgBox.exec();
    }
}

void Client::unlaunch() {
    this->loginpage->hide(); //MEMORY LEAK?
    this->show();
}
//Creation of login page.
bool Client::createPages() {
    return true;
}
void Client::showLoginPage() {
    this->hide();
    this->loginpage->show();
}

//Handles Connectivity Issues.
bool Client::prepareSocket(std::string serverAddressIP) {
    //Server address is the IP Address.
    //Take PORT as the predefined PORT.
    clientCTX = InitCTX();

    csock = socket(AF_INET, SOCK_STREAM , 0); //Creates the socket.
    if ( csock < 0 ) {
        return false;
    } else {

    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr( serverAddressIP.c_str());
    serverAddress.sin_port = PORT; //Predefined in INSTRUCTIONS.

    int rv = ::connect(csock, (struct sockaddr*) &serverAddress ,  sizeof(serverAddress)); // ::connect because Qt.

    //Now to SSL It.
    sslcsock = SSL_new(clientCTX);
    SSL_set_fd( sslcsock , csock );
    SSL_connect(sslcsock); //might fail.
    conn.setSocket(csock , sslcsock);
    ShowCerts(sslcsock);
    if ( rv < 0 ) {
        return false;
    } else {
        return true; //Assert : connection created.
    }
}


#endif
