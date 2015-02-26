#ifndef FILE_UPLOAD_CPP
#define FILE_UPLOAD_CPP
#include "client.h"

#include <fstream>
#include "../../common/communications.h"

bool Client::handleUpload() {
    //Assume that file name is given in data.
    if (data.filetype == NEW_FILE) {
        return this->uploadNewFile();
    } else if (data.filetype == DIFF_FILE ) {
        return this->uploadDiffFile();
    } else if ( data.filetype == REMOTE_DIFF ) {
        return this->uploadRemoteDiff();
    }
    return true;
}

bool Client::uploadNewFile() {
    //ASSERT : data.filetype == FILE_TYPE_NEW
    std::string filename = this->data.filename;
    std::fstream reader( filename );
    return conn.writeToSocket_file( reader , NEW_FILE);
}

bool Client::uploadDiffFile() {
    /*
     *The server calculates the diff file. The reason is processing speed ( assuming that the server is actually a server )
     *      The other part of the rationale is data transfer. We are minimizing data transferred by the user.
    */
    std::string filename = this->data.filename;
    std::fstream reader( filename );
    return conn.writeToSocket_file( reader , DIFF_FILE);

}

bool Client::uploadRemoteDiff() {
    std::string filename = this->data.filename;
    std::fstream reader(filename);
    /*
     *TODO :
     *Figure out this part.
    */
}

#endif
