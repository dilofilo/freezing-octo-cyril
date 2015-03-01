#ifndef USER_LOGIN_CPP
#define USER_LOGIN_CPP
#include "client.h"
#include "ui_loginpage.h"
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;
bool Client::handleLogin() {
    //Fetch Login details. - Done in the caller for this.
    //Send login details to a function which returns a bool.
    bool validUser = this->sendLogin( data.user.userID , data.user.password , data.user.clientDirectory); //No serverDir because thats on the end of the server.
    //return the value of the authenication
    if ( validUser ) {
        this->user.userID = data.user.userID;
        this->user.password = data.user.password;
        this->user.clientDirectory = data.user.clientDirectory; //NEED TO GET FROM THE SERVER.
        //Check Directories. If No Directory, make Directories + Log files.


        bfs::path cwd(bfs::current_path());
        bfs::path syncpath = cwd;
        bfs::path sharepath = cwd;
        syncpath /= (user.userID + "/" + CLIENT_SYNC_DIR) ;
        sharepath /= (user.userID + "/" +  CLIENT_SHARE_DIR );
        bfs::path syncfile = syncpath;
            syncfile /= ("/" + user.userID + CLIENT_SYNC_DIR);
        bfs::path sharefile = sharepath;
        sharefile /= ("/" + user.userID + CLIENT_SHARE_DIR);
        if( bfs::exists(syncpath) ) { //dir
        } else {
            bfs::create_directories(syncpath);
        }
        if (bfs::exists(syncfile)) { //file
        } else {
            this->createFileLog(syncfile.string());
        }
        if ( bfs::exists(sharepath) ) { //dir
        } else {
            bfs::create_directories(sharepath);
        }
        if ( bfs::exists(sharefile)) { //file

        } else {
            this->createFileLog(sharefile.string());
        }
        //Server files are taken from the dropbox thing. i,e after dropbox is created.
        //ASSERT : Created files.
        return true;
    } else {
        this->user.userID = "";
        this->user.password = "";
        this->user.clientDirectory = "";
        //TODO : Do Nothing.
        return false;
    }
}
//Log files for owner's uploaded files and another for shared files.
bool Client::createFileLog( std::string filename ) {
    //Directory already exists.
    fstream maker( filename , ios::out );//, ios::app); MAKE IN THE CLIENT DIRECTORY ITSELF.
    maker.close();
}

bool Client::handleLogout() {
    // to the launch screen.
    this->loginpage->show(); //Back to the square one.
    cout << "got here \n";
    delete this->dropboxpage;
    cout << "got here \n";
    return true;
}


/*
    MINION FUNCTIONS!
*/

bool Client::sendLogin( std::string& uid , std::string& pw , std::string& clidir) {
    //Write to the server and get the details back.
    /*
     *Send login request, read continue, send user details , read reply login details, read rejection/acceptance.
     */
    std::string temp( LOGIN_REQUEST );
    conn.writeToSocket(temp);
    //Read a continue.
    std::string temp2 = "";
    conn.readFromSocket(temp2);
    if ( !(temp2 == CONTINUE) ) {
        return false;
    }
    //Send User details function.
    conn.writeToSocket_user(data.user);
    UserDetails tempusr;
    conn.readFromSocket_user(tempusr);
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    conn.readFromSocket(temp2);
    if ( temp2 == LOGIN_ACCEPTED ) {
        data.user = tempusr;
        return true; //Saved on server side.
    } else {
        return false;
    }

}

#endif
