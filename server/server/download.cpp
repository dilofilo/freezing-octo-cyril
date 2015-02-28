
#ifndef DOWNLOAD_CPP
#define DOWNLOAD_CPP

#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

bool Server::handleDownload() {
    //I'm told that the file name will be sent to me.
    std::string cont(CONTINUE);
    conn.writeToSocket(cont); //write continue

    std::string filename = "";
    conn.readFromSocket(filename); //Gets the file to be downloaded.

    conn.writeToSocket(cont); //write a continue;

    std::string owner = "";
    conn.readFromSocket(owner);


    string filepath = SERVER_DIRECTORY + owner + "/" + filename ; //Sends the latest version.

    //reader.open(filepath.c_str(),ios::in);
    conn.writeToSocket_file(filepath); //correct file.

    std::string rcont;
    conn.readFromSocket(rcont); //read a continue.

    handleSync(user.userID);
    return true;
}


#endif
