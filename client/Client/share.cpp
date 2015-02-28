#ifndef SHARE_CPP
#define SHARE_CPP
#include "client.h"

bool Client::handleShare() {
    return true;
}

bool Client::handleUnshare() {
    return true;
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
