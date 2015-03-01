#ifndef COMMUNICATIONS_CPP
#define COMMUNICATIONS_CPP
#include <iostream>
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
#include <fstream>
#include <boost/filesystem.hpp>



#include "instructions.h"
//Constructors and Destructors.

std::string Communications::returnAllButFileName(std::string _p) {
    //Find the last dash and take a substring till there.
    int lastdash = _p.find_last_of("/");
    return _p.substr(0 , lastdash+1);
}
bool Communications::copy_directory_contents( bf::path& src , bf::path& dest)  {

    if ( boost::filesystem::create_directories(dest)){
        std::cout << "directory=" << dest.string() << " was created \n";
    }

    //Check if src is a file, if yes, copy it. Else, throw the directory into a source vector
    for ( bf::directory_iterator file(src) ; file != bf::directory_iterator() ; ++file) {
        //If its a file, copy, else call the same thing.
        boost::filesystem::path current = file->path();
        boost::filesystem::path destprime = (dest/(current.filename()));

        if ( boost::filesystem::is_directory(current) ) {
            copy_directory_contents( current , destprime );
        } else {
            copy( current , destprime );
        }
    }
    return true;
}




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

bool Communications::setSocket(Socket& sock, SSL* sl ) {
    csock = sock;
    sslsock = sl;
    return true;
}
int Communications::sendmyint(int num) {
    std::string msg = std::to_string(num);
    return this->writeToSocket(msg);
}
int Communications::receivemyint(int& num) {
    std::string str;
    this->readFromSocket(str);
    num = atoi(str.c_str());
    return true;
}

//char[] communication.

bool Communications::writeToSocket(char* buffer , int buf_size = BUFFER_SIZE) {
    int rv = SSL_write(sslsock, buffer, buf_size);
    //cout << " ######conn writing to socket (upto first nul character) " << buffer << "\n";
    if (rv>=0) {
        memset( buffer , 0 , buf_size );
        return true;
    } else {
        return false;
    }
}

bool Communications::readFromSocket( char* buffer, int buf_size = BUFFER_SIZE) { //Clears the buffer.
    memset( buffer , 0 , buf_size);
    int rv = SSL_read(sslsock, buffer, buf_size);
    if (rv>=0) {
        //std::cout << " #####conn read from buffer (upto first null character) " << buffer << "\n";
        return true;
    } else {
        return false;
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

//UserDetails code.
bool Communications::writeToSocket_user(UserDetails &usr) {
    /*
     *Done by :
     *write TRANSFER_BEGIN
     *read the appropriate reply.
    */
    UserDetails tempusr = usr;
    char beginbuf[BUFFER_SIZE];
    memset(beginbuf , 0 , BUFFER_SIZE);
    beginbuf[0] = TRANSFER_USER_BEGIN_CHAR;
    beginbuf[BUFFER_SIZE-1] = '0';

    bool rv = this->writeToSocket(beginbuf, BUFFER_SIZE);
    if ( !rv ) {
        return false;
    } else {
        //Read the instruction reply and decide.
        this->readFromSocket(beginbuf , BUFFER_SIZE);
        std::string temp(beginbuf);
        if ( temp == TRANSFER_USER_CONTINUE ) {
            //Continue out of this if-else block.
        } else {
            return false;
        }
    } // Apt reply read.

    //Continue the transfer.
    //write uid, read a continue.
    memset(beginbuf , 0 , BUFFER_SIZE);
    this->writeToSocket(tempusr.userID);
    this->readFromSocket(beginbuf , BUFFER_SIZE);
    if ( strcmp(beginbuf , TRANSFER_USER_CONTINUE)!=0 ) {
        return false;
    }
    memset(beginbuf , 0 , BUFFER_SIZE);
    this->writeToSocket(tempusr.password);
    this->readFromSocket(beginbuf , BUFFER_SIZE);
    if ( strcmp(beginbuf , TRANSFER_USER_CONTINUE)!=0 ) {
        return false;
    }
    memset(beginbuf , 0 , BUFFER_SIZE);
    this->writeToSocket(tempusr.clientDirectory);
    this->readFromSocket(beginbuf , BUFFER_SIZE);
    if ( strcmp(beginbuf , TRANSFER_USER_CONTINUE)!=0 ) {
        return false;
    }
    memset(beginbuf , 0 , BUFFER_SIZE);
    this->writeToSocket(tempusr.serverDirectory);
    this->readFromSocket(beginbuf , BUFFER_SIZE);
    if ( strcmp(beginbuf , TRANSFER_USER_CONTINUE)!=0 ) {
        return false;
    }
    //Write continue.
    memset(beginbuf , 0, BUFFER_SIZE);
    beginbuf[0] = TRANSFER_USER_END_CHAR;
    beginbuf[BUFFER_SIZE-1] = '0';
    this->writeToSocket(beginbuf , BUFFER_SIZE);
    return true;
} //They work.

bool Communications::readFromSocket_user(UserDetails &usr) {
    /*
     * Read the request,
    */
    UserDetails usr_buf; //Stores the read values temporarily.
    std::string temp( TRANSFER_USER_CONTINUE ); //Written multiple times
    char buf[BUFFER_SIZE]; //Used for writing/reading the initial instructions.
    memset( buf , 0, BUFFER_SIZE);
    bool rv = this->readFromSocket( buf , BUFFER_SIZE);

    if ( (!rv) || ( buf[0] != TRANSFER_USER_BEGIN_CHAR ) || (buf[BUFFER_SIZE-1] != '0') ) {
        return false;
    } else {
        //write the transfer request.
        memset(buf, 0 , BUFFER_SIZE);

        this->writeToSocket( temp );
    }

    //Assert : Now, read each field and write a confirmation.
    std::string uid = "";
    this->readFromSocket(uid);
    this->writeToSocket((temp));

    std::string pwd = "";
    this->readFromSocket(pwd);
    this->writeToSocket((temp));

    std::string clidir = "";
    this->readFromSocket(clidir);
    this->writeToSocket((temp));

    std::string serdir = "";
    this->readFromSocket(serdir);
    this->writeToSocket((temp));

    memset( buf , 0, BUFFER_SIZE);
    rv = this->readFromSocket( buf , BUFFER_SIZE);
    if ( rv && (buf[0] == TRANSFER_USER_END_CHAR) && (buf[BUFFER_SIZE-1] == '0') ) {
        usr.userID = uid;
        usr.password = pwd;
        usr.clientDirectory = clidir;
        usr.serverDirectory = serdir;
        return true;
    } //Done.
    return false;
}

//File Handling

bool Communications::writeToSocket_file_old( std::fstream& reader , FILE_MODE mode) { //Assumes that the reader is open and will be closed.
    //Assumes that C_TO_S_FILE has been written and stuff.
    char buf[FILE_TRANSFER_BUFFER_SIZE];
    memset( buf , 0, FILE_TRANSFER_BUFFER_SIZE);
    buf[0] = TRANSFER_FILE_BEGIN_CHAR;
    buf[FILE_TRANSFER_BUFFER_SIZE-1] = '0';
    this->writeToSocket( buf , FILE_TRANSFER_BUFFER_SIZE);
    std::string cont="";
    this->readFromSocket(cont);
    if ( cont!= CONTINUE) {
        return false;
    } //Sanity check.
    cont = "";


    char towrite[FILE_TRANSFER_BUFFER_SIZE];
    memset( towrite , 0 , FILE_TRANSFER_BUFFER_SIZE);
    //Read FILE_TRANSFER_BUFFER_SIZE Characters.
    reader.read( towrite , (FILE_TRANSFER_BUFFER_SIZE-1) );
    towrite[FILE_TRANSFER_BUFFER_SIZE-1] = '1'; //Keep Going.

    //File Writing part.
    while(!reader.eof()) {
        //Don't care about missing bits due to write().

        SSL_write( sslsock , towrite , FILE_TRANSFER_BUFFER_SIZE);
        memset(towrite , 0 , FILE_TRANSFER_BUFFER_SIZE);


        //Need to read continue - as a string.
        this->readFromSocket(cont);
        if ( cont!= CONTINUE) { //Wierd error.
            return false;
        } //Could have used TRANSFER_FILE_CONTINUE but that has been deprecated.
        cont="";
        //Read FILE_TRANSFER_BUFFER_SIZE Characters.
        reader.read( towrite , (FILE_TRANSFER_BUFFER_SIZE-1) );
        towrite[FILE_TRANSFER_BUFFER_SIZE-1] = '1'; //Keep Going.
    }

    //This code is here because the while loop reads the last bit without sending it.
    SSL_write( sslsock , towrite , FILE_TRANSFER_BUFFER_SIZE);
    memset(towrite , 0 , FILE_TRANSFER_BUFFER_SIZE);


    //Need to read continue - as a string.
    this->readFromSocket(cont);
    if ( cont!= CONTINUE) { //Wierd error.
        return false;
    }

    //END OF FILE SENDING.

    memset(buf , 0 , FILE_TRANSFER_BUFFER_SIZE);
    buf[0] = TRANSFER_FILE_END_CHAR;
    buf[FILE_TRANSFER_BUFFER_SIZE-1] = '0'; //DELIMITER
    return this->writeToSocket( buf , FILE_TRANSFER_BUFFER_SIZE);
} //reader should be closed by the supplier of the program.

bool Communications::readFromSocket_file_old(std::fstream &dest, FILE_MODE mode) {
    /*
     *READ: the file transfer char, write continue, read into the dest until the read value is not a file wali thing.
    */
    char buf[FILE_TRANSFER_BUFFER_SIZE];
    memset(buf, 0 ,FILE_TRANSFER_BUFFER_SIZE);
    this->readFromSocket( buf , FILE_TRANSFER_BUFFER_SIZE);
    std::string cont(CONTINUE);
    if ( (buf[0]==TRANSFER_FILE_BEGIN_CHAR) && (buf[FILE_TRANSFER_BUFFER_SIZE-1] == '0') ) {
        //write a continue!
        this->writeToSocket(cont);
    } else {
        return false;
    }
    //Now, read the file.
    bool moarfile = true;

    char fbuf[FILE_TRANSFER_BUFFER_SIZE];
    memset(fbuf , 0 , FILE_TRANSFER_BUFFER_SIZE);
    while ( moarfile ) {
        //Read into a buffer and check if its a 1 at the end.
        this->readFromSocket( fbuf , FILE_TRANSFER_BUFFER_SIZE);
        moarfile = ( fbuf[FILE_TRANSFER_BUFFER_SIZE-1] == '1'); //If it becomes a 0, its time to end.
        if ( moarfile ) {
            //write a continue.
            this->writeToSocket(cont);
        } else {
            break;
        }
    }
    return true;
    //End of transfer has been read already.
}

bool Communications::writeToSocket_file( std::string& readerfile , FILE_MODE mode) { //Assumes that the reader is open and will be closed.
    using namespace std;
    std::fstream reader;
    reader.open(readerfile , ios::in);
    //cout << "#####WRITING THE FOLLOWING FILE ONTO THE SOCKET \n\n\t\t" << readerfile << "\n\n\n";
    //Not gonna use poll. //Assumes that reader is open.
    std::string cont;
    char buf[FILE_TRANSFER_BUFFER_SIZE];
    memset(buf, 0 , FILE_TRANSFER_BUFFER_SIZE);
    buf[0] = TRANSFER_FILE_BEGIN_CHAR;
    buf[FILE_TRANSFER_BUFFER_SIZE-1] = '0';

    this->writeToSocket( buf , FILE_TRANSFER_BUFFER_SIZE);
    this->readFromSocket(cont);
    if (!( cont == CONTINUE )) {
        return false;
    }
    while( !reader.eof() ) {
        //Read a block from the file, write it into the fstream and then write the size of the block.
        //Read using f.gets to facilitate maintaining a counter for filedata size.
        int blocksize = 0;
        char filebuf[FILE_TRANSFER_BUFFER_SIZE];
        memset( filebuf , 0, FILE_TRANSFER_BUFFER_SIZE);
        char ch;
        while ( (blocksize < (FILE_TRANSFER_BUFFER_SIZE-1)) && (!(reader.eof()) ) ) { //It breaks at eof.
            reader.get(ch); //Read one character.
            filebuf[blocksize] = ch;
            blocksize++;
        } //Prepare what to write.
        filebuf[FILE_TRANSFER_BUFFER_SIZE-1] = '1'; //1 Represents more file to read.
        //cout << " #####the file was read as : " << filebuf << "\n" ;
        //cout << " #####the file size read was" << blocksize << "\n";
        //Done reading file aptly.
        //Write file into the stream and then read a continue, then an int, then a continue.
        this->writeToSocket( filebuf , FILE_TRANSFER_BUFFER_SIZE); //write the entire buffer. The int will convey what to read.
        this->readFromSocket( cont ); //Read a continue.
        //Now, write the int

        sendmyint( blocksize);
        this->readFromSocket(cont);
    }
    buf[0] = TRANSFER_FILE_END_CHAR;
    this->writeToSocket( buf , FILE_TRANSFER_BUFFER_SIZE);
    return true;
} //Writing file correctly.

bool Communications::readFromSocket_file( std::string& destfile , FILE_MODE mode) { //Assumes that the reader is open and will be closed.
    using namespace std;
    std::fstream dest;
    dest.open(destfile , ios::out);
    //cout << " ####WRITING INTO FILE NAME :" << destfile << "\n";
    std::string cont(CONTINUE);
    char buf[FILE_TRANSFER_BUFFER_SIZE];
    memset(buf, 0 , FILE_TRANSFER_BUFFER_SIZE);
    this->readFromSocket(buf , FILE_TRANSFER_BUFFER_SIZE); //Read file begin character
//    if ( ( (buf[0] == TRANSFER_FILE_BEGIN_CHAR) && ( buf[FILE_TRANSFER_BUFFER_SIZE-1] == '0'))) {
//         //Write a continue.
//    } else {
//        return false;
//    }
    this->writeToSocket(cont);//writing a continue.
    bool moarfile = true; //This will be transmitted across.
    while (moarfile) {
        //Read a string, an int and then write those many ints into the filestream
        char filebuf[FILE_TRANSFER_BUFFER_SIZE];
        memset( filebuf , 0 , FILE_TRANSFER_BUFFER_SIZE);
        this->readFromSocket(filebuf , FILE_TRANSFER_BUFFER_SIZE); //Read the buffer.

        moarfile = ( filebuf[FILE_TRANSFER_BUFFER_SIZE-1] == '1');
        if (!moarfile) {
            //Break.
            //If it was a '0', it means that the file was complete last time around.
            break;
        }
        //Read an int
        this->writeToSocket(cont); //Write a continue.
        int blocksize;
        receivemyint( blocksize );
        // write the file.
        //cout << " ###########going to write the following into the file : " << filebuf << "\n";
        dest.write( filebuf , blocksize );
        this->writeToSocket(cont); //Write a continue.
        //Now, write the file in.
    }
    dest.close();
    return true;
}

#endif
