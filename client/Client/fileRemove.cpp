#ifndef FILE_REMOVE_CPP
#define FILE_REMOVE_CPP
#include "client.h"

bool Client::handleRemove() {
    std::string req(REMOVE_REQUEST);
    conn.writeToSocket(req);
    std::string conti;
    conn.readFromSocket(conti);
    std::string filename = data.filename;
    conn.writeToSocket(filename);

    getServerFiles_login();
    this->dropboxpage->updateServerFiles();

    return true;
}
#endif
