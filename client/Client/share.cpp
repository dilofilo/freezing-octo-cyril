#ifndef SHARE_CPP
#define SHARE_CPP
#include "client.h"

bool Client::handleShare() {
    std::string filename = data.filename;
    std::string otheruser = data.other_user.userID;

    std::string cont;
    std::string conti(CONTINUE);
    std::string req(SHARE_REQUEST);
    conn.writeToSocket(req); //Write request
    conn.readFromSocket(cont); //read a continue
    conn.writeToSocket(otheruser); //Write the other user.
    //Read answer.
    std::string answer;
    conn.readFromSocket(answer);
    conn.writeToSocket(conti);
    this->getServerFiles_login();
    this->dropboxpage->updateServerFiles();
    //And we're done.
    return (answer == SHARE_ACCEPTED);
}

bool Client::handleUnshare() {
    std::string filename = data.filename;
    std::string otheruser = data.other_user.userID;

    std::string cont;
    std::string conti(CONTINUE);
    std::string req(UNSHARE_REQUEST);
    conn.writeToSocket(req); //Write request
    conn.readFromSocket(cont); //read a continue
    conn.writeToSocket(otheruser); //Write the other user.
    //Read answer.
    std::string answer;
    conn.readFromSocket(answer);
    conn.writeToSocket(conti);
    this->getServerFiles_login();
    this->dropboxpage->updateServerFiles();
    //And we're done.
    return (answer == UNSHARE_ACCEPTED);
}

bool Client::addToFileLog_shared(string uid, string fname, string _owner) {
    string logfilepath = uid + "/" + CLIENT_SHARE_DIR + "/" + uid + CLIENT_SHARE_DIR;
    fstream reader(logfilepath , ios::in);
    string logfilepathtemp = uid + "/" + CLIENT_SHARE_DIR + "/" + uid + CLIENT_SHARE_DIR + "temp";
    fstream writer(logfilepathtemp , ios::out);
    bool found = false;
    string file , owner;
    while ( !found ) {
        reader >> file;
        reader >> owner;
        if ( file == fname ) {
            found = true;
            file = fname;
            owner = _owner;
        }
        writer << file;
        writer << owner;
    }
    if ( !found ) {
        writer << fname << "\t" << _owner << "\n";
    }
    return true;
}

#endif
