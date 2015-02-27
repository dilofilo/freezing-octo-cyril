#ifndef INSTRUCTIONS_H
	#define INSTRUCTIONS_H

//Server related stuff
#define PORT 5000
#define MAX_CONNECTION_REQUESTS 10
#define POLL_TIMEOUT 15000

//Instructions to and from server
#define AUTH "AUTH"
#define REG "REG"
#define GETFILE "GETFILE"
#define RETFILE "RETFILE"

//Constants in messages
#define FILE_READ_CONTINUE '0'

//Size constants
#define FILE_BUF_SIZE 128

#endif