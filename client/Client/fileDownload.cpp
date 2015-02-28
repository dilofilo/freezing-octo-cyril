#ifndef FILE_DOWNLOAD_CPP
#define FILE_DOWNLOAD_CPP

#include "client.h"
#include <boost/filesystem.hpp>
int findverfile(string& srcfile , string& findfile); //Given a file it, returns the file version downloaded during download.
bool Client::handleDownload() {
    //Comes with file and owner.
    cout << "#### data.filename\t" << data.filename << "\ndata.other_user\t" << data.other_user.userID << "\n";
    cout << " brk 1 \n";
    string uid = user.userID;
    cout << " brk 2 \n";
    string req(S_TO_C_FILE);
    conn.writeToSocket(req);
    cout << " brk 3 \n";
    string cont;
    conn.readFromSocket(cont); //read continue.
    cout << " brk 4 \n";
    //File name should be in data.filename;
    string processedfname = processFileName(data.filename); //Gets file name here.
    string owner = data.other_user.userID;
    cout << " brk 5 \n";
    conn.writeToSocket( processedfname );
    cout << " brk 6 \n";
    conn.readFromSocket(cont);
    conn.writeToSocket(owner);
    cout << " brk 7 \n";
    //Reading the file.
    string temppath = user.userID + "/mytempfile";
    cout << " brk 8 \n";
    conn.readFromSocket_file( temppath , NEW_FILE);
    cout << " brk 9 \n";

    std::string conti(CONTINUE);
    conn.writeToSocket(conti);
    cout << " brk 10 \n";
    this->getServerFiles_login(); //Have the two things updated.
    cout << " brk 11 \n";
    this->dropboxpage->updateServerFiles(); //Doesn't care about the downloaded section.
    cout << " brk 12 \n";
    //Now i need to get the version;
    string src = uid + "/" + CLIENT_SYNC_DIR + "/" + SERVER_LOG;
    //string completepath = findFilePath(src , processedfname);

    cout << " brk 13 " << temppath << "\n";
    int version = findverfile( src , processedfname); //handles the cases where the file is a shared file too.
    cout << " brk 14 \n";
    bool wasasyncfile = (owner == user.userID);
    cout << " brk 15 \n";
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
    cout << " brk 16 \n";
    return true;
}

int findverfile(string& srcfile , string& findfile){
    fstream f;
//    string fi = uid + "/" + CLIENT_SYNC_DIR + "/" + SERVER_LOG ;
//    f.open(fi.c_str());   //GIVE ME THE FILENAME
    f.open(srcfile.c_str());
    string s1;
    int ver = 0;
    int temp;

    while(f){
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
