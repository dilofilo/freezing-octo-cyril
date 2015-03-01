#ifndef UPLOAD_CPP
#define UPLOAD_CPP

#include <stdio.h>
#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <sys/stat.h> //for mkdir and its related definitions.

std::string returnAllButFileName(string _p) {
    //Find the last dash and take a substring till there.
    int lastdash = _p.find_last_of("/");
    return _p.substr(0 , lastdash+1);
}

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
    string myfilepass_dir = returnAllButFileName(myfilepass);
    boost::filesystem::path myfilepass_dir_path(myfilepass_dir);
    if ( boost::filesystem::exists(myfilepass_dir_path)) {

    } else {
        boost::filesystem::create_directories(myfilepass_dir_path);
    }
    bool made = conn.readFromSocket_file( myfilepass , NEW_FILE ) ;
    if( made ){
        int version = CheckifFileExists(finame , user.userID);

        AddFile(finame , version , user.userID);
        /*if(version > 1){
            // file exists.
            AddFile(finame , version+1 , user.userID);
        }
        else{
            AddFile(finame , version+1 , user.userID);
        }*/ //VERSION IS NOW KNOWN.

        conn.writeToSocket(cont);
        std::string lal;

        conn.readFromSocket(lal);

        string ver = to_string(version+1);
        conn.writeToSocket(ver);
        cout << " done writing version \n";

        /*
         *Files storage : latest version is present freely. diff files in v1...vn
        */
        if (version == 1) {
            string old_name = myfilepass;
            string new_name =SERVER_DIRECTORY + user.userID + "/" + finame;
            string new_name_dir = SERVER_DIRECTORY + user.userID + "/";
            boost::filesystem::path new_name_dir_path( new_name_dir );
            //Now, make their paths and rename.
            boost::filesystem::path pathold(old_name.c_str() );
            boost::filesystem::path pathnew(new_name.c_str() );
            if ( exists(new_name_dir_path)) {
                //Nothing to do. just throw it in.
            } else {
                boost::filesystem::create_directories(new_name_dir_path);
            }

            boost::filesystem::rename(pathold , pathnew);
        } else { //Will never happen.
            string prior = SERVER_DIRECTORY + user.userID + "/" + finame; //The latest present in DB before the new upload
            string vminus1 = SERVER_DIRECTORY + user.userID + "/v_" + to_string(version-1) + "/" + finame;
            string old_name = myfilepass; //Uploaded file.
            boost::filesystem::path pathprior(prior.c_str() );
            boost::filesystem::path pathvm1(vminus1.c_str() );
                //Move prior to vm1
            boost::filesystem::rename(pathprior , pathvm1);
            boost::filesystem::path pathprior_updated(prior.c_str() );
            boost::filesystem::path pathold_name(old_name.c_str() );
            boost::filesystem::rename(pathold_name , pathprior_updated );
        }
        std::string cont;
        conn.readFromSocket(cont);
        handleSync( user.userID );
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
