#ifndef FILE_TO_SERVER_CPP
	#define FILE_TO_SERVER_CPP
#include <poll.h>
#include <server.cpp>
#include "utility.cpp"
#include "instructions.h"

void Server::mainFileToServer()
{
		bool cont =true;
		string filename;
		getFileNameFromClient(filename);
		char buffer[FILE_BUF_SIZE];
		std::fstream filestream( filename , ios::app );
		while(cont)
		{
			cont = readFileFromClient(buffer);
     		writeToFile( buffer , filestream);
     	}
}


bool Server::getFileNameFromClient(std::string& filename) {
	//Read from csock.
	char fname_buffer[FILE_BUF_SIZE];
	if(readFromSocket(csock , fname_buffer , FILE_BUF_SIZE)) {
		std::string t(fname_buffer); //Convert chararacter array to string.
		filename = t;
		return true;
	} else {
		return false;
	}
}

bool readFileFromClient( buffer ) {
	readFromSocket(csock , buffer , FILE_BUF_SIZE);
	//assert : buffer now contains the thing to write.
	return processFileBuffer( buffer , FILE_BUF_SIZE);

	/*if (buffer[FILE_BUF_SIZE-1] == FILE_READ_CONTINUE) {
		return true;
	} else {
		return false;
	}*/
}

void writeToFile( char* buffer , std::fstream& f) { //f is the filestream , buffer is what to write.
	std::string t(buffer);
	f << t;
	return;
}

bool processFileBuffer( char* buffer , int b_size = FILE_BUF_SIZE) {
	if (buffer[ b_size-1 ] == FILE_READ_CONTINUE) {
		return true;
	} else {
		//Read buffer[b_size] - '0'
		int lastIDX = (int)(buffer[ b_size-1 ]); //buffer[b_size]
		
		return false;
	}
}
#endif