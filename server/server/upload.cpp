#ifndef UPLOAD_CPP
#define UPLOAD_CPP

#include <stdio.h>
#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include <sys/stat.h> //for mkdir and its related definitions.

bool Server::handleUpload() {
    //I'm told that the file name will be sent to me.
    /*
     *The upload instruction has already been read. Now i must send a continue and then receive the file.
    */
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    std::fstream dest;
    string finame;
    bool fileuploadmode = getFilestream(dest , finame);
    //FILE_MODE mode = ((fileuploadmode)?(DIFF_FILE):(NEW_FILE));
    //ASSERT : dest is now open.
    string myfilepass = SERVER_DIRECTORY + user.userID + "/" + TEMPPREFIX + finame;
    bool made = conn.readFromSocket_file( myfilepass , NEW_FILE ) ;
    if( made ){
        int version = CheckifFileExists(finame , user.userID);

        if(version > 0){
            // file exists.
            AddFile(finame , version+1 , user.userID);
        }
        else{
            AddFile(finame , version+1 , user.userID);
        } //VERSION IS NOW KNOWN.
        cout << " server writing continue \n";
        conn.writeToSocket(cont);
        std::string lal;
        cout << " server reading continue \n";
        conn.readFromSocket(lal);
        cout << " writing version" << to_string(version+1) << "\n";
        string ver = to_string(version+1);
        conn.writeToSocket(ver);
        cout << " done writing version \n";
            // Moving the previous version for persistant storage.
            string olname = SERVER_DIRECTORY + user.userID + "/" + finame;
            string sub_finame = finame.substr(4); //Ignore the size of TEMPPREFIX
            string newname = SERVER_DIRECTORY + user.userID + "/" + "v_" + to_string(version+1) + "/" + sub_finame;

            cout << "server renaming " << olname << "\t to \t" << newname << "\n";
            boost::filesystem::path pathol(olname.c_str() );
            boost::filesystem::path pathnew(newname.c_str() );
            boost::filesystem::rename(pathol , pathnew);
//        }

//        string olname = SERVER_DIRECTORY + user.userID + "/" + TEMPPREFIX + finame;
//        string newname = SERVER_DIRECTORY + user.userID + "/" + finame;
//        rename(olname.c_str() , newname.c_str());       // renaming the temporary file.

    } else {
        return false;
    }
    return true;
}

bool Server::getFilestream( std::fstream& dest, string& finame ) { //Returns if the file exists already or not.
    std::string filename = "";
    conn.readFromSocket( filename );
    cout << processFileName(filename) << " will soon to uploaded to the server \n";
    finame= filename;
    std::string cont(CONTINUE);
    conn.writeToSocket( cont );
    //dest.open( processFileName(filename).c_str() , ios::out);
    return false;
}

std::string Server::processFileName( std::string filename ) {
    /*
     * TODO : Figure out what the server equivalent of the file is.
    */
    string foobar = SERVER_DIRECTORY + user.userID + "/" + TEMPPREFIX + filename; // Change the path here.
    return  foobar;
}

#endif
