#ifndef FILE_UPLOAD_CPP
#define FILE_UPLOAD_CPP
#include "client.h"

#include <fstream>
#include "../../common/communications.h"

bool Client::handleUpload() {
    //Assume that file name is given in data.
    //Read a continue first.
    //Write C_TO_S first?
    std::string cmd( C_TO_S_FILE );
    conn.writeToSocket(cmd);
    std::string cont;
    conn.readFromSocket(cont);
    uploadNewFile(); //Who cares for the other two?
    return true;
}

bool Client::uploadNewFile() {
    //ASSERT : data.filetype == FILE_TYPE_NEW
    std::string filename = this->data.filename;
    std::fstream reader;
    reader.open(filename ); //In mode.
    conn.writeToSocket(filename);
    std:string cont;
    conn.readFromSocket(cont);
    return conn.writeToSocket_file( reader , NEW_FILE);
}

bool Client::uploadDiffFile() { //UNIMPLEMENTED
    /*
     *The server calculates the diff file. The reason is processing speed ( assuming that the server is actually a server )
     *      The other part of the rationale is data transfer. We are minimizing data transferred by the user.
    */
    std::string filename = this->data.filename;
    std::fstream reader( filename );
    conn.writeToSocket(filename);
    return conn.writeToSocket_file( reader , DIFF_FILE);

}

bool Client::uploadRemoteDiff() { //UNIMPLEMENTED
    std::string filename = this->data.filename;
    std::fstream reader(filename);
    /*
     *TODO :
     *Figure out this part.
    */
}

#endif
