#ifndef FILE_DOWNLOAD_CPP
#define FILE_DOWNLOAD_CPP

#include "client.h"
#include <boost/filesystem.hpp>
int findverfile(string& srcfile , string& findfile); //Given a file it, returns the file version downloaded during download.

bool Client::handleDownload() {

    //Comes with file and owner.
    //Data.filename is relative path, wrt ClientDirectory.

    string uid = user.userID;
    string req(S_TO_C_FILE);
    conn.writeToSocket(req);
    string cont;
    conn.readFromSocket(cont); //read continue.

    string owner = data.other_user.userID; //Should be me.


    conn.writeToSocket( data.filename ); //Write file name

    conn.readFromSocket(cont);

    conn.writeToSocket(owner);
    //Reading the file.

    string finalpath = user.userID + "/" + CLIENT_SYNC_DIR + "/" + data.filename ;
    string finalpathdir = conn.returnAllButFileName(finalpath);
    boost::filesystem::path finalpathdirpath( finalpathdir);
    if (boost::filesystem::exists(finalpathdirpath)) {
    } else {
        boost::filesystem::create_directories(finalpathdirpath);
    }
    conn.readFromSocket_file( finalpath , NEW_FILE); //READING THE FILE INTO THE CORRECT LOCAITON.

    std::string conti(CONTINUE);
    conn.writeToSocket(conti);

    this->getServerFiles_login(); //Have the two things updated.
    this->dropboxpage->updateServerFiles(); //Doesn't care about the downloaded section.
    //Now i need to get the version; Yes, indeed.

    string src = uid + "/" + CLIENT_SYNC_DIR + "/" + SERVER_LOG;
            //string completepath = findFilePath(src , processedfname); WHAT?
    int version = findverfile( src , data.filename); //handles the cases where the file is a shared file too.
    this->addToFileLog( user.userID , data.filename , finalpath , version );

    return true;
}

bool Client::handleSharedDownload() {

    string fn = data.filename;
    string owner = data.other_user.userID;
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
    string filepathdir = conn.returnAllButFileName(filepath);
    boost::filesystem::path filepathdir_p(filepathdir);
    if ( boost::filesystem::exists(filepathdir_p)) {

    } else {
        boost::filesystem::create_directories(filepathdir_p);
    }
    conn.readFromSocket_file(filepath);
    conn.writeToSocket(cont);
    //Update files.
    this->getServerFiles_login();
    this->dropboxpage->updateServerFiles();
//    this->addToFileLog_shared( user.userID , fn , owner);
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
    f.close();
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
    reader.close();
    return "\0"; //Put file into pwd();
}

#endif
