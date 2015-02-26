
#ifndef DOWNLOAD_CPP
#define DOWNLOAD_CPP

#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

bool Server::handleDownload() {
    //I'm told that the file name will be sent to me.
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    std::string file = "";
    return conn.writeToSocket(file); //Gets the file to be downloaded.
}

#endif
