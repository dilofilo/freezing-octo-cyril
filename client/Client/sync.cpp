#ifndef SYNC_CPP
#define SYNC_CPP
#include "client.h"
#include "clientdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

#include <unordered_map>
#include <boost/filesystem.hpp>

using namespace std;
bool Client::handleSync() {
    string syncreq(SYNC_REQUEST);
    conn.writeToSocket(syncreq); //Write sync request
    string tempfile = user.userID + LOG_FILE_SUFFIX;
    conn.readFromSocket_file(tempfile); //Assert : File ready.
    set<string>  filenames;
    unordered_map<string , int> fileversions; //Valid for all files.
    unordered_map<string , string> fileowners; //File owners.
    populateFileData_login_normal(filenames , fileversions , fileowners);
    populateFileData_login_shared(filenames , fileversions , fileowners);
    return true;
}

void Client::getServerFiles_login() { //Puts them into the dropbox.
    cout << "getting server log files\n";
    //Assert : The Server is sending log files accross.
    string syncfilename = user.userID + "/" + CLIENT_SYNC_DIR + "/" +SERVER_LOG;
    //Put file into that file name.
    conn.readFromSocket_file(syncfilename); //Read and saved the file in the Client directory. Need to remove this file once done.
    //Assert : saved the first Log File already.
    /* log keeping idea : filename,filepath, owner, */
    //CLEAR THE DROPBOX HASHTABLES
    this->dropboxpage->filenames.clear();
    this->dropboxpage->fileowners.clear();
    this->dropboxpage->fileversions.clear();

    populateFileData_login_normal( this->dropboxpage->filenames , this->dropboxpage->fileversions , this->dropboxpage->fileowners); //Populate the maps.

    cout << "got normal server log file \n";
    std::string cont(CONTINUE);
    conn.writeToSocket(cont); //Write a continue.

    string sharefilename = user.userID + "/" + CLIENT_SHARE_DIR +"/" +  SERVER_LOG;
    conn.readFromSocket_file(sharefilename); //Read the shared files
    populateFileData_login_shared( this->dropboxpage->filenames , this->dropboxpage->fileversions , this->dropboxpage->fileowners); //Populate the maps.
    cout << " got server shared log file \n";
    //These maps need to go to dropboxpage.
}

void Client::populateFileData_login_normal(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string>& fo) {

    //Read the file and use it aptly.
    string tfn = user.userID + "/" + CLIENT_SYNC_DIR + "/" + SERVER_LOG;
    string trash;

    fstream reader(tfn , ios::in);
    reader >> trash; reader >> trash ; reader >> trash ; reader >> trash ;
    //File is of the form : filename , version
    while(!reader.eof()) {
        string fname;
        int version;
        reader >> fname;
        reader >> version;
        fn.insert(fname);
        fv[fname] += 1;
        fo[fname] = user.userID;
    }
    reader.close();
}

void Client::populateFileData_login_shared(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string>& fo) {
    string tfn = user.userID + "/" + CLIENT_SHARE_DIR + "/" + SERVER_LOG;
    fstream reader(tfn , ios::in);
    //File is of the form : filename , version
    string trash; reader >> trash ; reader >> trash ; reader >> trash  ;reader >> trash ;reader >> trash ;
    while(!reader.eof()) {
        string fname;
        string owner;
        reader >> fname;
        reader >> owner;
        fn.insert(fname);
        fo[fname] = owner;
    }
    reader.close();
} //Assert : Read the file.


#endif
