#ifndef FILE_DOWNLOAD_CPP
#define FILE_DOWNLOAD_CPP

#include "client.h"
#include <boost/filesystem.hpp>
int findverfile(string& srcfile , string& findfile); //Given a file it, returns the file version downloaded during download.

bool Client::handleDownload() {

    //Comes with file and owner.
    cout << "#### data.filename\t" << data.filename << "\ndata.other_user\t" << data.other_user.userID << "\n";

    string filedir = conn.returnAllButFileName(data.filename);
    boost::filesystem::path filedir_path(filedir);
    if (boost::filesystem::exists(filedir)) {

    } else {
        boost::filesystem::create_directories(filedir_path);
    }

    string uid = user.userID;
    string req(S_TO_C_FILE);
    conn.writeToSocket(req);
    string cont;
    conn.readFromSocket(cont); //read continue.
    //File name should be in data.filename;
    string processedfname = processFileName(data.filename); //Gets file name here.
    string owner = data.other_user.userID;
    conn.writeToSocket( processedfname );
    conn.readFromSocket(cont);
    conn.writeToSocket(owner);
    //Reading the file.
    string temppath = user.userID + "/mytempfile";
    conn.readFromSocket_file( temppath , NEW_FILE);

    std::string conti(CONTINUE);
    conn.writeToSocket(conti);
    this->getServerFiles_login(); //Have the two things updated.
    this->dropboxpage->updateServerFiles(); //Doesn't care about the downloaded section.
    //Now i need to get the version;
    string src = uid + "/" + CLIENT_SYNC_DIR + "/" + SERVER_LOG;
    //string completepath = findFilePath(src , processedfname);

    int version = findverfile( src , processedfname); //handles the cases where the file is a shared file too.
    bool wasasyncfile = (owner == user.userID);

    if ( wasasyncfile ) {
        string filepath = uid + "/" + CLIENT_SYNC_DIR + "/" + processedfname;
        if ( filepath == "\0") {
            return false;
        }
        boost::filesystem::path newloc( filepath );
        boost::filesystem::path oldloc( temppath );
        boost::filesystem::rename( oldloc , newloc );
        this->addToFileLog(user.userID , processedfname , newloc.string() , version);
    } else {
        string filepath = uid + "/" + CLIENT_SHARE_DIR + "/" + processedfname;

        boost::filesystem::path newloc( filepath );
        boost::filesystem::path oldloc( temppath );
        boost::filesystem::rename( oldloc , newloc );
        this->addToFileLog_shared(uid , processedfname , owner);
    }
    return true;
}

bool Client::handleSharedDownload() {

    string fn = processFileName(data.filename);
    string owner = data.other_user.userID;
    cout << "filename=" << fn << " and owner=" << data.other_user.userID<< "\n";
    string req(S_TO_C_SHARED);
    conn.writeToSocket(req);
    string conti;
    string cont(CONTINUE);
    conn.readFromSocket(conti);
    conn.writeToSocket(fn);
    conn.readFromSocket(conti);
    conn.writeToSocket(owner);
    conn.readFromSocket(conti);
    conn.writeToSocket(cont);

    string filepath = user.userID + "/" + CLIENT_SHARE_DIR + "/" + fn;
    cout << " downloading file to" << filepath << "\n";
    conn.readFromSocket_file(filepath);
    conn.writeToSocket(cont);
    //Update files.
    this->getServerFiles_login();
    this->dropboxpage->updateServerFiles();
    cout << " updated server files \n";
//    this->addToFileLog_shared( user.userID , fn , owner);
    cout << "added to file log ";
}

int findverfile(string& srcfile , string& findfile){
    fstream f;
//    string fi = uid + "/" + CLIENT_SYNC_DIR + "/" + SERVER_LOG ;
//    f.open(fi.c_str());   //GIVE ME THE FILENAME
    f.open(srcfile.c_str());
    string s1;
    int ver = 0;
    int temp;

    while(f) {
        f>>s1>>temp;
        if(s1.compare(findfile) == 0){
            if(temp > ver){
                ver = temp;
            }
        }
    }
    if (ver!=0) return ver;
    else return 1; //Shared file?
}

string Client::findFilePath( string src, string pfn) { //pfn is processed filename
    fstream reader( src , ios::in );
    string f,p,v;
    while(!(reader.eof())) {

        reader >> f;
        reader >> p;
        reader >> v;

        if ( f== pfn ) {
            return p;
        }
    }
    return "\0"; //Put file into pwd();
}

#endif
