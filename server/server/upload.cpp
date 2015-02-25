#ifndef UPLOAD_CPP
#define UPLOAD_CPP

#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

bool Server::handleUpload() {
    //I'm told that the file name will be sent to me.
    /*
     *The upload instruction has already been read. Now i must send a continue and then receive the file.
    */
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    std::fstream dest;
    bool fileuploadmode = getFilestream(dest);
    EDIT_MODE mode = ((fileuploadmode)?(EDIT):(NEW));
    //ASSERT : dest is now open.
    return conn.readToSocket_file( dest , mode );
}

bool Server::getFilestream( std::fstream& dest ) { //Returns if the file exists already or not.
    std::string filename = "";
    conn.readFromSocket( filename );
    cout << filename << "will soon to uploaded to the server \n";
    std::string cont(CONTINUE);
    conn.writeToSocket( cont );
    dest.open( processFileName(filename).c_str());
    return false;
}

std::string Server::processFileName( std::string filename ) {
    /*
     * TODO : Figure out what the server equivalent of the file is.
    */
    return filename;
}

#endif
