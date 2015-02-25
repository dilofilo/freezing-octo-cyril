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

#include "instructions.h"
#include "communications.h"
#include "communications.cpp"

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

void setup();
void gclient();
bool getInstruction();
void handleClient();
int main(int argc char** argv) {
	setup();
	gclient();
}

void setup() {
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
	int myport;
	cout << "Enter port = ";
	cin >> myport;
	cout << "\n";
	serverAddr.sin_port = myport;

	if ( bind( ssock , (struct sockaddr * ) &serverAddr , sizeof(serverAddr)) < 0 ) {
        printf(" socket binding failed... \n");
		exit(1);
	} else {
        printf(" socket successfully binded... \n");
	}	
	//Assert : ssock is now ready - there is one incoming connection.
	gclient();
}

void gclient() {
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

bool getInstruction( std::string& inst ) {
    inst = "";
    printf( " waiting for instructions \n");
    return conn.readFromSocket( inst );
}

void handleClient() {
	    while ( true ) {
        if ( getInstruction(instruction) ) { //Also sets instruction = ""
            if (handleInstruction(instruction) ) { //Returns if the handler was succesful, take appropriate action.
                cout << instruction;
                printf( " Instruction handled successfully \n");
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

bool handleInstruction(std::string& inst) {
	if ( inst == "ping" ) {
		cout << "ping received \n";
		conn.writeToSocket( inst );
		return true;
	} else if (inst == "chat" ) {
		cout << "chat initiated \n";
		cout << "enter your message \n";
		string msg = "";
		string inp = "";
		while ( msg != "exit" ) {
			
		}
		return true;
	} else if ( inst == "upload" ) {

	}

}