#ifndef COMMUNICATIONS_CPP
#define COMMUNICATIONS_CPP

/**
    Defines functions for the class Communicaitons defined in communicaitons.h
    Sorry for the eye-sore lines in Qt's vim(dark) theme.
    Also, uint was used instead of int because Qt things that (uint == int) is a scary prospect.

*/

#include "communications.h"

//unnecessary incudes. TODO: REMOVE THESE UNNECESSARY INCLUDES.
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

//Constructors and Destructors.
Communications::Communications() {
    //Do Nothing to the sockets.
}

Communications::~Communications() {
    //Do Nothing.
}


//Socket creation and setting and deletion
Socket Communications::getSocket() {
    return csock;
}

bool Communications::setSocket(Socket& sock) {
    csock = sock;
    return true;
}

//char[] communication.

bool Communications::writeToSocket(char* buffer , int buf_size = BUFFER_SIZE) {
    struct pollfd wPoll;
    wPoll.fd = csock;
    wPoll.events = POLLOUT;

    int rv = poll( &wPoll , 1 , POLL_TIMEOUT);
    if ( rv < 0 ) { //Poll unsuccessful
        #ifdef SERVER_SIDE
        printf(" poll was unsuccessful for some reason. \n");
        #endif
        exit(1);
        return false;
    } else if( rv==0 ) { //Poll timeout occurred
        #ifdef SERVER_SIDE
        printf(" poll timeout \n");
        #endif
        return true;
    } else {
        //Poll was successful
        if ( wPoll.revents & POLLOUT) {
            rv = write(csock, buffer, buf_size);
            if (rv>=0) {
                #ifdef SERVER_SIDE
                printf(" writing was successful \n");
                #endif
                memset( buffer , 0 , buf_size );
                return true;
            } else {
                #ifdef SERVER_SIDE
                printf(" ERROR!!!! writing was NOT successful \n");
                #endif
                return false;
            }
        } else {
            return false;
        }
    }
}

bool Communications::readFromSocket( char* buffer, int buf_size = BUFFER_SIZE) { //Clears the buffer.
    memset( buffer , 0 , buf_size);
    struct pollfd rPoll;
    rPoll.fd = csock;
    rPoll.events = POLLIN;

    int rv = poll( &rPoll , 1 , POLL_TIMEOUT);
    if ( rv < 0 ) { //Poll unsuccessful
        #ifdef SERVER_SIDE
        printf(" poll was unsuccessful for some reason. \n");
        #endif
        return false;
        exit(1);
    } else if( rv==0 ) { //Poll timeout occurred
        #ifdef SERVER_SIDE
        printf(" poll timeout \n");
        #endif
        return true;
    } else {
        //Poll was successful
        if ( rPoll.revents & POLLIN ) {
            rv = read(csock, buffer, buf_size);
            if (rv>=0) {
                #ifdef SERVER_SIDE
                printf(" Reading was successful \n");
                #endif
                return true;
            } else {
                #ifdef SERVER_SIDE
                printf(" ERROR!!!! reading was NOT successful \n");
                #endif
                return false;
            }
        } else {
            return false;
        }
    }
}
//End of char[] definitions

//String involving functions.

bool Communications::writeToSocket( std::string& buffer , int buf_size ) {
    //Clears the string.
    if ( buf_size != BUFFER_SIZE ) {
        printf(" WARNING! writeToSocket() called with BUFFER_SIZE changed. \n");
    } else {

    }
    char nbuffer[BUFFER_SIZE];
    for(int pos=0; pos < buf_size ; pos++) {
        if ( pos < buffer.size()) {
            nbuffer[pos] = buffer[pos];
        } else {
            nbuffer[pos] = 0;
        }
    }

    return writeToSocket( nbuffer ,  buf_size);
}

bool Communications::readFromSocket(std::string& buffer , int buf_size ) {
    buffer =""; //Clear it.
    bool returnvalue = false;
    if (buf_size != BUFFER_SIZE ) {
        printf(" WARNING! readFromSocket() called with BUFFER_SIZE changed. \n");
    } else {
        char tempArr[BUFFER_SIZE];
        returnvalue = readFromSocket( tempArr , BUFFER_SIZE );
        std::string tempString(tempArr);
        buffer = tempString;
    }
    return returnvalue;
}

//End of string functions

//Beginning of infinite write/read functions.

bool Communications::writeToSocket( std::vector< std::string >& strings ) { //Assume that all of them are of the correct size. That should be enough for now.
    /*
        General Idea :
        :::BEGIN::: Write the INFINITE_TRANSFER_BEGIN_CHAR with a '1' at the end .
           :::WRITE::: Write all the strings if they are length INFINITE_TRANSFER_BUFFER_SIZE. and a '0' at the end.
        :::END::: Write the INFINITE_TRANSFER_END_CHAR with a '1' at the end.
    */
    struct pollfd wPoll;
    wPoll.fd = csock;
    wPoll.events = POLLOUT;
    int rv = poll( &wPoll , 1 , POLL_TIMEOUT);


    //:::BEGIN:::
    if ( rv < 0 ) { //Poll unsuccessful
        #ifdef SERVER_SIDE
        printf(" poll was unsuccessful for some reason. \n");
        #endif
        return false;
    } else if( rv==0 ) { //Poll timeout occurred
        #ifdef SERVER_SIDE
        printf(" poll timeout \n");
        #endif
        return true;
    } else {
        //Poll was successful
        char buffer[BUFFER_SIZE];
        buffer[0] = INF_TRANSFER_BEGIN_CHAR;
        buffer[INF_TRANSFER_BUFFER_SIZE] = '1';
        rv = write(csock, buffer, BUFFER_SIZE);

        if (rv>0) {
            #ifdef SERVER_SIDE
            printf(" writing was successful \n");
            #endif
        } else {
            #ifdef SERVER_SIDE
            printf(" ERROR!!!! writing was NOT successful \n");
            #endif
            return false;
        }
    }

    //:::WRITE:::
    for(uint i=0; i< strings.size() ; ++i) {
        char tempArr[BUFFER_SIZE];
        for(int pos = 0; pos < BUFFER_SIZE; ++pos) {
            tempArr[pos] = strings[i][pos];
        }
        tempArr[INF_TRANSFER_BUFFER_SIZE] = '0';
        bool returnvalue = writeToSocket( tempArr , BUFFER_SIZE);
        if ( !returnvalue ) {
            return false;
        }
    }
    //:::END:::
    wPoll.fd = csock;
    wPoll.events = POLLOUT;
    rv = poll( &wPoll , 1 , POLL_TIMEOUT);
    if ( rv < 0 ) { //Poll unsuccessful
        #ifdef SERVER_SIDE
        printf(" poll was unsuccessful for some reason. \n");
        #endif
        return false;
    } else if( rv==0 ) { //Poll timeout occurred
        #ifdef SERVER_SIDE
        printf(" poll timeout \n");
        #endif
        return true;
    } else {
        //Poll was successful - assume that the event was revents = POLLIN
        if ( wPoll.revents & POLLOUT ) {
            char buffer[BUFFER_SIZE];
            buffer[0] = INF_TRANSFER_END_CHAR;
            buffer[INF_TRANSFER_BUFFER_SIZE] = '1';
            rv = write(csock, buffer, BUFFER_SIZE);

            if (rv>0) {
                #ifdef SERVER_SIDE
                printf(" writing was successful \n");
                #endif
                return true;//we're done!
            } else {
                #ifdef SERVER_SIDE
                printf(" ERROR!!!! writing was NOT successful \n");
                #endif
                return false;
            }
        }
    }
    return false;
}

bool Communications::readFromSocket( std::vector< std::string >& strings ) { //Assume that all of them are of the correct size. That should be enough for now.
/*
 *General idea is :
    :::BEGIN::: Read the INF_TRANSFER_BEGIN_CHAR with a '1' at the end.
    ::READ::: If you read a buffer with a '0' at the end,
    :::END::: Ends within Read,
*/
    //:::BEGIN:::
    struct pollfd rPoll;
    rPoll.fd = csock;
    rPoll.events = POLLIN;

    char buffer[BUFFER_SIZE];
    memset(buffer, 0 , BUFFER_SIZE);
    int rv = poll( &rPoll , 1 , POLL_TIMEOUT);
    if ( rv < 0 ) { //Poll unsuccessful
        #ifdef SERVER_SIDE
        printf(" poll was unsuccessful for some reason. \n");
        #endif
        return false;
    } else if( rv==0 ) { //Poll timeout occurred
        #ifdef SERVER_SIDE
        printf(" poll timeout \n");
        #endif
        return true;
    } else {
        //Poll was successful
        rv = read(csock, buffer, BUFFER_SIZE);
        if (rv>0) {
            #ifdef SERVER_SIDE
            printf(" Reading was successful \n");
            #endif
        } else {
            #ifdef SERVER_SIDE
            printf(" ERROR!!!! reading was NOT successful \n");
            #endif
            return false;
        }
    }
    if ( (buffer[0] == INF_TRANSFER_BEGIN_CHAR) && ( buffer[INF_TRANSFER_BUFFER_SIZE] == '0' ) ) {
        //Continue;
    } else {
        return false; // Did not request an infinite transfer.
    }

    //:::READ:::
    while(true) {
        //Read into a buffer, if the buffer is the end of the transfer, break out. else, push it into the vector.
        rPoll.fd = csock;
        rPoll.events = POLLIN;
        rv = poll( &rPoll , 1 , POLL_TIMEOUT);
        if ( rv < 0 ) {
            #ifdef SERVER_SIDE
            printf(" poll was unsuccessful for some reason. \n");
            #endif
            return false;
        } else if ( rv == 0 ) {
            #ifdef SERVER_SIDE
            printf(" poll timeout \n");
            #endif
            return true;
        } else {
            if ( rPoll.revents & POLLIN ) {
                //polling happened. now, just read the darned value, check it its what we want.
                memset( buffer , 0 , BUFFER_SIZE);
                rv = read( csock, buffer , BUFFER_SIZE);
                //If it matches with the end of transfer token, break, else push it into the vector.
                if ( (buffer[0] == INF_TRANSFER_END_CHAR) && (buffer[INF_TRANSFER_BUFFER_SIZE] == '0')) {
                    return true;
                } else {
                    std::string tempStr( buffer );
                    strings.push_back(tempStr);
                }
            }
        }
    }
}

#endif
