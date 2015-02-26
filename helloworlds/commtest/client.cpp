using namespace std;
#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include "arpa/inet.h"
#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

    Socket csock;
    struct sockaddr_in serverAddress, clientAddress;
    //struct hostent* server_entity; Not necessary.
    std::string serverAddress_string;

    Communications conn; // following that old PHP-SQL stile maen. \_|_/
bool Client::prepareSocket(std::string serverAddressIP) {
    //Server address is the IP Address.
    //Take PORT as the predefined PORT.
    csock = socket(AF_INET, SOCK_STREAM , 0); //Creates the socket.
    if ( csock < 0 ) {
        return false;
    } else {

    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr( serverAddressIP.c_str());
    int myport;
    cout << "enter port\n";
    cin >>myport;
    serverAddress.sin_port = myport; //Predefined in INSTRUCTIONS.

    int rv = ::connect(csock, (struct sockaddr*) &serverAddress ,  sizeof(serverAddress)); // ::connect because Qt.
    if ( rv < 0 ) {
        return false;
    } else {
        conn.setSocket(csock);
        return true; //Assert : connection created.
    }
}

int main(int argc, char** argv) {
	string serverip = "";
	cout << "enter ip\n";
	cin >> serverip;
	prepareSocket
}