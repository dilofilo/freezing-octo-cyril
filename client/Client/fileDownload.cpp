#ifndef FILE_DOWNLOAD_CPP
#define FILE_DOWNLOAD_CPP

#include "client.h"
#include <boost/filesystem.hpp>

bool Client::handleDownload() {
    string req(S_TO_C_FILE);
    conn.writeToSocket(req);
    string cont;
    conn.readFromSocket(cont); //read continue.
    //File name should be in data.filename;
    string processedfname = processFileName(data.filename);
    conn.writeToSocket( processedfname );

    conn.readFromSocket(cont);

    string completepath = findFilePath(processedfname);
    //
    //fstream writer( findFilePath( processedfname) , ios::out);
    std::string tempfn = findFilePath( processedfname);
    conn.readFromSocket_file( tempfn , NEW_FILE);
    return true;
}

string Client::findFilePath( string pfn) { //pfn is processed filename
    fstream reader( user.userID , ios::in );
    while(!(reader.eof())) {
        string f,p;
        int v;
        reader >> f;
        reader >> p;
        reader >> v;

        if ( f== pfn ) {
            return p;
        }
    }
    fstream writer( user.userID , ios::app );
    boost::filesystem::path cwd( boost::filesystem::current_path() );
    writer << pfn << cwd << 1 << "\n";
    return pfn; //Put file into pwd();
}

#endif
