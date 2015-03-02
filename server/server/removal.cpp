#ifndef REMOVAL_CPP
#define REMOVAL_CPP

#include "server.h"
#include <string>
#include <stdio.h>
#include "serverdefinitions.h"
#include <boost/filesystem.hpp>

bool Server::handleRemoveFile(){
    //Assert : Given command to REMOVE FILE.
    //Tell it to continue, then read the file name.
    string cont(CONTINUE);
    conn.writeToSocket(cont);
    string f;
    conn.readFromSocket(f);
    bool rv= removeFile(f);
    handleSync(user.userID);
    return rv;
}
bool Server::removeFile(string filename) {

    string currentfile = SERVER_DIRECTORY + user.userID + "/" + filename; //currentfile is the file to be removed next.
    //Delete it from databases.
    string uid = user.userID;

    string a,b,c,d,e;
    //DATABASE MODIFICATIONS
    int ctr=0;
    db.open();
    QSqlQuery counting; //Count the number of versions of the file.
    a = " SELECT FILENAME,VERSION FROM "; b = USERTABLE ;c = " WHERE FILENAME='" ; d="' AND OWNER='"; e="';";
    string q1 = a + b + c + currentfile + d + uid + e;
    QString qq1  = QString::fromStdString(q1);
    counting.exec(qq1);
    while( counting.next() ) {
        ctr++;
    }

    a =  "DELETE FROM "; b = USERTABLE; c =" WHERE FILENAME='"; d = "' AND OWNER='"; e="';";
    QSqlQuery deletion;
    q1 = a + b + c + currentfile + d + uid + e;
    qq1 = QString::fromStdString(q1);
    deletion.exec(qq1); //Deletes the query from user files.

    a =  "DELETE FROM "; b = SHAREDTABLE; c =" WHERE FILENAME='"; d = "' AND OWNER='"; e="';";
    q1 = a + b + c + currentfile + d + uid + e;
    qq1 = QString::fromStdString(q1);
    deletion.exec((qq1));
    db.close();

    //Delete the latest file first.
    boost::filesystem::path curr(currentfile);
    if ( boost::filesystem::exists(curr) ) {
        boost::filesystem::remove(curr);
        cout << "deleted latest file\n";
    }

    //Now to delete it from every version.
    for(int i=1; i<ctr;++i) {
        currentfile = SERVER_DIRECTORY + user.userID +"/v_" + to_string(i) + "/" + filename;
        //Now, remove the file.
        cout << "deleted version=" << i << "\n";
        boost::filesystem::path curri (currentfile );
        if ( boost::filesystem::exists(curri) ) {
            boost::filesystem::remove(curri);
        }
    }
    return true;
}

#endif
