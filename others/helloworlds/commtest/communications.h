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
#include <fstream> //For file transfer.
#include "instructions.h"


typedef int Socket;

enum SECURITY {
    OPEN_SSL , NO_SLL
};

enum FILE_MODE { NEW , DIFF , REMOTE_DIFF};
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

    // Used for Login and Register.
    bool writeToSocket_user( UserDetails& usr); //Do it bit by bit.
    bool readFromSocket_user( UserDetails& usr); //Do it bit by bit.

    //Used for Files - WORKS ONLY FOR NEW AND DIFF FILES.
    bool writeToSocket_file( std::fstream& source , FILE_MODE mode = NEW); //Read character by character, put it into a buffer and send it across.
    bool readToSocket_file( std::fstream& dest , FILE_MODE mode=NEW); //Read a chunk from the buffer and write it into the destination
    //Note : Sockets are closed by callers, not by communications.

    //REMOTE DIFF - TO BE IMPLEMENTED.


};

#endif // COMMUNICATIONS_H
