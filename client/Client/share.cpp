#ifndef SHARE_CPP
#define SHARE_CPP
#include "client.h"

bool Client::handleShare() {
    return true;
}

bool Client::handleUnshare() {
    return true;
}

bool Client::addToFileLog_shared(string uid, string fname, string owner) {
    fstream maker(uid+SHARED_EXTN , ios::app);
    maker << fname << "\t" << owner << "\n";
    maker.close();
    return true;
}

#endif
