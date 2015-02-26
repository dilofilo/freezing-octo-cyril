#ifndef LOGIN_CPP
#define LOGIN_CPP
#include"server.h"
#include"../../common/communications.h"
#include"../../common/instructions.h"
#include <string>

bool Server::handleLogin()
{
    string cont( CONTINUE );
    conn.writeToSocket(cont);
    struct UserDetails usr;
    readFromSocket_user( usr );
    if(authenticate(usr.userID , usr.password) == true )
    {
        // Modify the struct and send it back.
        string temp;
        conn.readFromSocket( temp );
        if ( temp.compare( CONTINUE ) == 0 ){
            string acc (LOGIN_ACCEPTED);
            conn.writeToSocket(acc);
        }
    }
    else{
        conn.writeToSocket_user( usr );
        string temp;
        conn.readFromSocket( temp );
        string fail( LOGIN_REJECTED );
        conn.write( fail );
        return false;
    }
}

bool Server::handleLogout() {
    //Forget user details.
    this->user.userID = "";
    this->user.clientDirectory = "";
    this->user.password = "";
    this->user.serverDirectory = "";
    return true;
    //Done.
}

#endif
