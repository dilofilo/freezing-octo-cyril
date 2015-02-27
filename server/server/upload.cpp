#ifndef UPLOAD_CPP
#define UPLOAD_CPP

#include <stdio.h>
#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
#include <fstream>
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
    FILE_MODE mode = ((fileuploadmode)?(DIFF_FILE):(NEW_FILE));
    //ASSERT : dest is now open.
    if(conn.readFromSocket_file( dest , mode )){

        ifstream f;
        ofstream f1;
        int ver;
        string loc = SERVER_DIRECTORY + this->user.userID + "/" + MYFILES;
        f.open(loc);
        string loc1 = SERVER_DIRECTORY + this->user.userID + "/" + TEMP;
        f1.open(loc1);
        int max = 0;
        int myver = 0;
        string filename;

        int version = CheckifFileExists(finame , user.userID);

        if(version > 0){
            // file exists.
            AddFile(finame , version+1 , user.userID);
        }

        else{
            AddFile(finame , version+1 , user.userID);
        }

        string olname = TEMPPREFIX + finame;
        rename(olname.c_str() , finame.c_str() );

        if(myver != 0){
            // A file with the same name exists.

                string foo = to_string(myver);

            if(myver > max){

                string mystr = SERVER_DIRECTORY + this->user.userID + "/v_" + foo;
                int status = mkdir( mystr.c_str() , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if(status == 0){
                    cout<<"Directory created\n";

                    return true;

                }else{
                    cout<<"Not Created\n";
                    return false;
                }
            }
            // Moving the previous version.
            string newname = "v_" + foo + "/" + foo + "_" + finame;
            rename(finame.c_str() , newname.c_str() );
        }
        else{
            rename(loc1.c_str() ,loc.c_str() );
            return true;
        }

    }

//        while(f){
//            f>>filename>>ver;
//            if(ver > max)     max=ver;

//            if(filename.compare(finame) == 0)
//            {
//            // File Exists hence version modified.
//                f1<<finame<<"\t"<<ver+1<<"\n";
//                myver = ver+1;
//            }
//            else{
//                f1<<filename<<"\t"<<ver<<"\n";
//            }
//        }

//        f.close();
//        f1.close();

        rename(TEMP,MYFILES);


    else return false;
}

bool Server::getFilestream( std::fstream& dest, string& finame ) { //Returns if the file exists already or not.
    std::string filename = "";
    conn.readFromSocket( filename );
    cout << filename << "will soon to uploaded to the server \n";
    finame=filename;
    std::string cont(CONTINUE);
    conn.writeToSocket( cont );
    dest.open( processFileName(filename).c_str());
    return false;
}

std::string Server::processFileName( std::string filename ) {
    /*
     * TODO : Figure out what the server equivalent of the file is.
    */
    string foobar = TEMPPREFIX + filename;
    return  foobar;
}

#endif
