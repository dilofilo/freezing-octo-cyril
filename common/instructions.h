#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <string>

struct UserDetails {
    std::string userID;
    std::string password;
    std::string serverDirectory;
    std::string clientDirectory;
};

//Server side definitions. Do not interfere.
#ifdef SERVER_SIDE
    #undef SERVER_SIDE
    #define SERVER_SIDE
#endif // This little bit of code is here only so that you know that the server has a definition called SERVER_SIDE

//Client side definitions. Do not interfere.
#ifdef CLIENT_SIDE
    #undef CLIENT_SIDE
    #define CLIENT_SIDE
#endif // This little bit of code is here only so that you know that the client has a definition called CLIENT_SIDE

//Connection Requirements.
#define PORT 5000
#define MAX_CONNECTION_REQUESTS 10
#define POLL_TIMEOUT 15000
#define CLIENT_URL_LEN 255
    //Poll timeout is 15s.

//Buffer Sizes
#define BUFFER_SIZE 255
#define INF_TRANSFER_BUFFER_SIZE 254
#define FILE_TRANSFER_BUFFER_SIZE 1024
    //File Transfer Buffer Size is different.
/*INF_TRANSFER_BUFFER_SIZE must always be BUFFER_SIZE-1
    FILE_TRANSFER_BUFFER_SIZE must always be BUFFER_SIZE-1.
*/
//Instructions.

    //CONTINUE is used to specify that the next instruction can be sent.
    #define CONTINUE "GO_ON"

    //Connection Testing
    #define PING_REQUEST "PING"
    #define PING_ACCEPTED "PINGBACK"

    //Exitter INSTRUCTIONS
    #define EXIT_REQUEST "EXIT"

    //Registraiton and authentication
    #define REGISTRATION_REQUEST "REG"
        #define REGISTRATION_REJECTED "REG_REJECTED"
        #define REGISTRATION_ACCEPTED "REG_ACCEPT"
    #define LOGIN_REQUEST "LOGIN"
        #define LOGIN_REJECTED "LOGIN_REJECTED"
        #define LOGIN_ACCEPTED "LOGIN_ACCEPTED"
#define LOGOUT "LOGOUT"
    //Individual File Transfer and download
    #define C_TO_S_FILE "C_TO_S_FILE"
        //The above one is upload
    #define S_TO_C_FILE "S_TO_C_FILE"
        //The above one is download.

    //File removal.
    #define REMOVE_REQUEST "REMOVEDEMFILES"

    //Revert
#define REVERT_REQUEST "REVERTPLIZ"
    //File Sync
    #define SYNC_REQUEST "SYNCPLIZ"

    //FILE_MODE is a enum declared in communications.
    //Sharing
    #define SHARE_REQUEST "SHARE"
    #define SHARE_ACCEPTED "SHARED"
    #define SHARE_REJECTED "NOSHARE"
    //Unsharing
    #define UNSHARE_REQUEST "UNSHARE"
    #define UNSHARE_ACCEPTED "UNSHARED"
    #define UNSHARE_REJECTED "NOUNSHARE"

//Infinite Buffer Instructions.
#define INF_TRANSFER_BEGIN_CHAR 'X'
#define INF_TRANSFER_END_CHAR 'X'

//For transferring UserDetails - used in Communications in the *_user() functions
#define TRANSFER_USER_BEGIN_CHAR 'U'
#define TRANSFER_USER_CONTINUE "GO_ON"
#define TRANSFER_USER_END_CHAR 'U'

//For transferring Files - used in Communications in the *_file() functions

#define TRANSFER_FILE_BEGIN_CHAR 'F'
#define TRANSFER_FILE_CONTINUE_CHAR 'C'
#define TRANSFER_FILE_END_CHAR 'F'
    //Both of these instructions will be accompanied with buffer[INF_TRANSFER_BUFFER_SIZE] = '0'

#endif // INSTRUCTIONS_H
