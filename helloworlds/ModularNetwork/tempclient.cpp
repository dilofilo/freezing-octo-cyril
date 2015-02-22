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
#include "instructions.h"
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define PORT 5000
#define BUF_SIZE 255
int main(int argc, char** argv) {
    
    struct sockaddr_in addr, cl_addr;
    int sockfd, ret;
    char buffer[BUF_SIZE];    
    struct hostent * server;  
    char * serverAddr;  

    if(argc < 2) {
        cout << "enter the server name. \n";
        exit(1);
    }
    serverAddr = argv[1];
    //Make socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);    
    if (sockfd<0) {
        cout << "couldn't make soccet bro\n";
        exit(1);
    }
    memset( buffer , 0 , BUF_SIZE);
    addr.sin_family = AF_INET;    
    addr.sin_addr.s_addr = inet_addr(serverAddr);  
    addr.sin_port = PORT;       

    ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));    
    if (ret <0 ) {
        cout << "failed to connect ... \n";
        exit(1);
    }
    memset(buffer , 0, BUF_SIZE);

    printf("enter your message \n");
    while ( fgets(buffer, BUF_SIZE , stdin) != NULL) {
        ret = write(sockfd , buffer , BUF_SIZE);
        if (ret<0) {
            cout << "error sending data \n";
        }
        struct pollfd mp;
            mp.fd = sockfd;
            mp.events = POLLIN;

        ret = poll(&mp , 1 ,15000);
        if ( mp.revents & POLLIN) {
            ret = read(sockfd , buffer , BUF_SIZE);
        }
        cout << " server replied with " << buffer << "\n";
    }


}