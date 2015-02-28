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
    //Assert : The Server is sending log files accross.
    string filename = user.userID + LOG_FILE_SUFFIX;
    //Put file into that file name.
    conn.readFromSocket_file(filename); //Read and saved the file in the Client directory. Need to remove this file once done.
    //Assert : saved the first Log File already.
    /* log keeping idea : filename,filepath, owner, */
    populateFileData_login_normal( this->dropboxpage->filenames , this->dropboxpage->fileversions , this->dropboxpage->fileowners); //Populate the maps.

    std::string cont(CONTINUE);
    conn.writeToSocket(cont); //Write a continue.

    conn.readFromSocket_file(filename); //Read the shared files
    populateFileData_login_shared( this->dropboxpage->filenames , this->dropboxpage->fileversions , this->dropboxpage->fileowners); //Populate the maps.
    boost::filesystem::remove(filename); //Remove the file.
    //These maps need to go to dropboxpage.
}

void Client::populateFileData_login_normal(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string> fo) {
    //Read the file and use it aptly.
    string tfn = user.userID + LOG_FILE_SUFFIX;
    fstream reader(tfn , ios::in);
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

void Client::populateFileData_login_shared(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string> fo) {
    string tfn = user.userID + LOG_FILE_SUFFIX;
    fstream reader(tfn , ios::in);
    //File is of the form : filename , version
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

//bool Client::populateSyncFileList() {
//    fstream f,f1;
//    f.open(user.userID , ios::in);
//    f1.open(user.userID + LOG_FILE_SUFFIX , ios::in);
//    unordered_map <string , int> m,m1;
//    unordered_map<string , int>::iterator it;

//    string sttemp;
//    int intemp;

//    while(f){
//        f>>sttemp>>intemp;
//        it = m.find(sttemp);
//        if(it == m.end()){
//            // The enry does not exist.
//            m[sttemp] = 1;
//        }
//        else{
//            m[sttemp]++;
//        }

//    }

//    while(f1){
//        f1>>sttemp>>intemp;

//        it = m1.find(sttemp);
//        if(it == m1.end()){
//            // The enry does not exist.
//            m1[sttemp] = 1;
//        }
//        else{
//            m1[sttemp]++;
//        }

//    }

//    // both hash tables filled.
//    // Based on the entries in the hash tables, upload or download the files.
//}

#endif
