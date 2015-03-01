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

bool Server::handleUpload() {

    /*
     *The upload instruction has already been read. Now i must send a continue and then receive the file.
    */
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    string finame;

    conn.readFromSocket( finame ); //Get file name

    conn.writeToSocket( cont ); //write continue to socket.

    string myfilepass = SERVER_DIRECTORY + user.userID + "/" + TEMPPREFIX + finame; //Put the file here? Yes, because we need to do version control, hence we keep it in a temp locaton

    string myfilepass_dir = conn.returnAllButFileName(myfilepass); //Get the directory into which the file should go.

    cout << "###detected filepath is" << myfilepass_dir << "\n";

    boost::filesystem::path myfilepass_dir_path(myfilepass_dir);
    if ( boost::filesystem::exists(myfilepass_dir_path)) { //If path doesn't exist, make it.
        cout << "it exists\n";
    } else {
        cout << "creation\n";
        boost::filesystem::create_directories(myfilepass_dir_path);
        cout << "created\n";
    }

    cout << "about to read the file into" << myfilepass << "\n";
    bool made = conn.readFromSocket_file( myfilepass , NEW_FILE ) ; //Read the file.


    if( made ){
        int version = CheckifFileExists(finame , user.userID);
        AddFile(finame , version , user.userID);

        conn.writeToSocket(cont);

        std::string lal;
        conn.readFromSocket(lal);

        cout << "writing version \n";
        std::string ver = to_string(version+1);
        conn.writeToSocket(ver);
        cout << " done writing version \n";

        /*
         *Files storage : latest version is present freely. diff files in v1...vn
        */
        if (version == 1) { //New file.
            string old_name = myfilepass; //temp file.
            string new_name =SERVER_DIRECTORY + user.userID + "/" + finame; //Correct location.

            boost::filesystem::path old_dir_path(conn.returnAllButFileName(old_name));
            if ( exists(old_dir_path)) {
            } else {
                boost::filesystem::create_directories(old_dir_path);
            }

            boost::filesystem::path new_dir_path(conn.returnAllButFileName(new_name));
            if ( exists(new_dir_path)) {
            } else {
                boost::filesystem::create_directories(new_dir_path);
            }

            //Checked for existence of all directories.
            //Now, make their paths and rename.
            boost::filesystem::path pathold(old_name);
            boost::filesystem::path pathnew(new_name);
            boost::filesystem::rename(pathold , pathnew);

        } else { // Old versions.

            string prior = SERVER_DIRECTORY + user.userID + "/" + finame; //The latest present in DB before the new upload
            boost::filesystem::path prior_dir_path(conn.returnAllButFileName(prior));
            if ( exists(prior_dir_path)) {
            } else {
                boost::filesystem::create_directories(prior_dir_path);
            }
            string vminus1 = SERVER_DIRECTORY + user.userID + "/v_" + to_string(version-1) + "/" + finame; //Where the latest version should go.
            boost::filesystem::path vm1_dir_path(conn.returnAllButFileName(vminus1));
            if ( exists(vm1_dir_path)) {
            } else {
                boost::filesystem::create_directories(vm1_dir_path);
            }

            string old_name = myfilepass; // latest file , presently in temp location
            boost::filesystem::path old_dir_path(conn.returnAllButFileName(old_name));
            if ( exists(old_dir_path)) {
            } else {
                boost::filesystem::create_directories(old_dir_path);
            }

            //Checked for existence of all those paths.
            boost::filesystem::path pathprior(prior);
            boost::filesystem::path pathvm1(vminus1);
                //Move prior to vm1
            boost::filesystem::rename(pathprior , pathvm1);


            boost::filesystem::path pathprior_updated(prior.c_str() );
            boost::filesystem::path pathold_name(old_name.c_str() );
            boost::filesystem::rename(pathold_name , pathprior_updated );
        }
        std::string cont;
        conn.readFromSocket(cont);
        handleSync( user.userID );

        //Handle The Deletion of temp folders. //Temp Folder will be inside MBD/DIRECTORIES/userID/
        int firstdash = finame.find_first_of("/");
        //Cases: firstdash == end of finame
        if ( firstdash == string::npos ) { //Cant find it - must be a file.
        } else { //There is a backslash, means that the thing was a folder.
            string p = finame.substr(0 , firstdash);
            p = SERVER_DIRECTORY + user.userID + "/" + TEMPPREFIX + p;
            cout << "deleting the path=" << p << "\n";
            boost::filesystem::path pp(p);
            boost::filesystem::remove_all(pp);
        }

    } else {
        return false;
    }

    return true;
}

bool Server::getFilestream( std::fstream& dest, string& finame ) { //Returns if the file exists already or not.
    std::string filename = "";

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
