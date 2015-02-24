#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H
/**
    This class can be used to read and write from the socket it contains.
    Must have for every server and client, really.
*/

//Classes for networking etc.
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "arpa/inet.h"

#include <stdio.h>  //for printf.
#include <string.h> //For memset

#include <string> //For simplicity.
#include <vector> //For infinite string transfer


#include <poll.h> //For synchronousness

#include "instructions.h"


typedef int Socket;

enum SECURITY {
    OPEN_SSL , NO_SLL
};


class Communications {
private:
    Socket csock;
public:

       //Constructors and destructors.
    Communications();
    ~Communications();

    Socket getSocket();
    bool setSocket(Socket& sock);

    //Single Read and write using char[]
    bool writeToSocket( char* buffer , int buf_size);// buf_size = BUFFER_SIZE );
    bool readFromSocket( char* buffer , int buf_size);// buf_size = BUFFER_SIZE );

    //Read and write using string
    bool writeToSocket( std::string& buffer , int buf_size= BUFFER_SIZE);
    bool readFromSocket( std::string& buffer , int buf_size=BUFFER_SIZE);

    //Infinite Read and write.
    bool writeToSocket( std::vector< std::string >& strings );
    bool readFromSocket( std::vector< std::string >& strings );

    //Note : Sockets are closed by callers, not by communications.
};

#endif // COMMUNICATIONS_H
