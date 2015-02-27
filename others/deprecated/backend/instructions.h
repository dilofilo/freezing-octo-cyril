#ifndef INSTRUCTIONS_H
	#define INSTRUCTIONS_H

//Server related stuff
#define PORT 5000
#define MAX_CONNECTION_REQUESTS 10
#define POLL_TIMEOUT 15000

//PING Instructions
#define REQUEST_PING "HI"
#define ACCEPT_PING "HI"

//Instructions to and from server
#define AUTH "AUTH"
#define ACCEPT_AUTH_REQUEST "AUTH_ACCEPTED"
#define REG "REG"
#define GETFILE "GETFILE"
#define RETFILE "RETFILE"
 
#define  ACCEPT_USERNAME "UID_ACCEPTED"
#define VALID_USER "VALID"
#define INVALID_USER "INVALID"
#define GIVE_DIR "WRITE"
#define TRANSFER_DONE "DONE"


//Constants in messages
#define FILE_READ_CONTINUE '0'

//Size constants
#define FILE_BUF_SIZE 128
#define INSTR_BUF_SIZE 255

#endif