#ifndef DATABASE_CPP
#define DATABASE_CPP
/*
This file handles with reading databases and reading user's file directory etc.
SQLite DB Table has :
USERNAME
PASSWORD
SERVER_DIR
CLIENT_DIR

the table is called #defined TABLE_NAME
Host is LOCAL_HOST
TODO list.
*/
#include "server.h"
#include "serverdefinitions.h"
#include <string>
#include <sstream>
#include <QString>
bool Server::main_CreateDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(LOCAL_HOST);
    db.setDatabaseName(DATABASE);
    db.setUserName(ADMIN_ID);
    db.setPassword(ADMIN_PW);
    // If the table TABLE_NAME doesnt exist, make it.
    bool db_open =  db.open(); //Should open the database.
    cout << "opening the database resulted in" << db_open << "\n";
    QSqlQuery table_exists;
    string p1("SELECT name FROM sqlite_master WHERE type='table' AND name='");
    string p2(TABLE_NAME);
    string p3("';");
    table_exists.exec( (p1 + p2 + p3).c_str() ); //tells me if the table exists.
//    while( table_exists.next() ) {
//        cout << " table already exists \n";
//        return true;
//    }
    CreateTable();
    CreateTableuser();
    Createtableshared();
    return true;
}

bool Server::main_CreateDictionary() {
    if ( !db.isOpen() ) {
        db.open(); //Ensures that the db is open.
    }
    QSqlQuery getall;
    string p1("SELECT * FROM ");
    string p2( TABLE_NAME );
    string p3(";");
    getall.exec( (p1+p2+p3).c_str() );
    while( getall.next() ) {
        //Add user to database.
        string usr, pwd , clidir , serdir;
        usr = getall.value(0).toString().toUtf8().constData();
        pwd = getall.value(1).toString().toUtf8().constData();
        clidir = getall.value(2).toString().toUtf8().constData();
        serdir = getall.value(3).toString().toUtf8().constData();
        UserDetails usr_struct;
            usr_struct.userID = usr;
            usr_struct.password = pwd;
            usr_struct.clientDirectory = clidir;
            usr_struct.serverDirectory = serdir;
        this->userDetails[usr] = usr_struct;
    }
    db.close();
    return true;
}


bool Server::CreateTableuser() {
    //Assert : This is called only if the table doesnt already exist.
    if ( !db.isOpen() ) {
        db.open();
    }
    cout << "making table \n";
    QSqlQuery creator;
    string p1("CREATE TABLE ");
    string p2(USERTABLE);
    string p3("(");
    string p4("FILENAME         VARCHAR(50) NOT NULL,");
    string p5("VERSION          INTEGER NOT NULL," );
    string p7("OWNER            VARCHAR(50) NOT NULL);");
    creator.exec( (p1+p2+p3+p4+p5+p7).c_str() );
    db.close();
    return true;
}

int Server::CheckifFileExists(string finame , string owner){
    if ( !db.isOpen() ) {
        db.open();
    }
    QSqlQuery fetcher;

    string p1("SELECT VERSION FROM ");
    string p2(USERTABLE);
    string p3(" where FILENAME='");
    string p4("' AND OWNER='");
    string p5("';");
    fetcher.exec((p1 +p2 + p3 + finame + p4 + owner + p5).c_str());
    int ctr = 0;
    while ( fetcher.isSelect() && fetcher.next() ) {
        ctr++;
    }
    db.close();
    return ctr+1;
}

bool Server::AddFile(string finame, int version , string owner){
    if ( !db.isOpen() ) {
        db.open();
    }
    cout << " now adding file intro usertable owner=" << owner << "\n";
    string c1 =" VALUES('";
    string c2 ="','";
    string c3 ="');";

    string myval = c1 + finame + c2 + to_string(version) + c2 + owner + c3;
    QSqlQuery inserter;
    string p1("INSERT INTO " );
    string p2(USERTABLE);
    //string p3(" (FILENAME,VERSION,OWNER) ");
    inserter.exec( (p1+p2+myval).c_str());
    cout << " done executing AddFile() \n";
    db.close();
    return true;
}

bool Server::Createtableshared(){

    //Assert : This is called only if the table doesnt already exist.
    if ( !db.isOpen() ) {
        db.open();
    }
    cout << "making table \n";
    QSqlQuery creator;
    string p1("CREATE TABLE ");
    string p2(SHAREDTABLE);
    string p3("(");
    string p4("FILENAME         VARCHAR(50) NOT NULL,");
    string p5("USER             VARCHAR(50) NOT NULL," );
    string p7("OWNER            VARCHAR(50) NOT NULL);");
    creator.exec( (p1+p2+p3+p4+p5+p7).c_str() );
    db.close();
    return true;
}

bool Server::SyncController( string uID ){
    fstream f; //present in server directory.
    string fn = uID + "log.txt";
    f.open( fn , ios::out ); //Always sends log.txt accross.
    f<<"THIS FILE IS SPECIAL"<<endl;
    if ( !db.isOpen() ) {
        db.open();
    }
    QSqlQuery fetcher;
    string p1("SELECT FILENAME,VERSION FROM ");
    string p2(USERTABLE);
    string p4(" WHERE OWNER='");
    string p5("';");
//    cout << " ## ## ## \nexecuting command :" << (p1 +p2 + p4 + uID + p5).c_str() << "\n ## ## ##";
    fetcher.exec((p1 +p2 + p4 + uID + p5).c_str());
    while ( fetcher.isSelect() && fetcher.next() ) {
//        cout << fetcher.value(0).toString().toUtf8().constData() << "\t" << fetcher.value(1).toInt() << "\n";
        f << fetcher.value(0).toString().toUtf8().constData() << "\t" << fetcher.value(1).toInt() << "\n";
    }
    db.close();
    f.close();
    return true;

}


bool Server::SyncControllerShared( string uID ){
    fstream f;
    string fn = uID + "log.txt";
    f.open( fn.c_str() ,ios::out); //Refresh the file.
    f<<"THIS FILE IS SHARED SPECIAL"<<endl;
    if ( !db.isOpen() ) {
        db.open();
    }
    QSqlQuery fetcher;

    string p1("SELECT FILENAME,OWNER FROM ");
    string p2(SHAREDTABLE);
    string p4(" WHERE USER='");
    string p5("';");
    cout << " ## ## ## \nexecuting command :" << (p1 +p2 + p4 + uID + p5).c_str() << "\n ## ## ##";
    fetcher.exec((p1 +p2 + p4 + uID + p5).c_str());
    while ( fetcher.isSelect() && fetcher.next() ) {
        cout << fetcher.value(0).toString().toUtf8().constData() << "\t" << fetcher.value(1).toString().toUtf8().constData() << "\n";
        f<<fetcher.value(0).toString().toUtf8().constData()<<"\t"<<fetcher.value(1).toString().toUtf8().constData()<<"\n";
    }
    db.close();
    f.close();
    return true;
}

bool Server::CreateTable() {
    //Assert : This is called only if the table doesnt already exist.
    if ( !db.isOpen() ) {
        db.open();
    }
    cout << "making table \n";
    QSqlQuery creator;
    string p1("CREATE TABLE ");
    string p2(TABLE_NAME);
    string p3("(");
    string p4("USERNAME         VARCHAR(50) PRIMARY KEY NOT NULL,");
    string p5("PASSWORD         VARCHAR(50) NOT NULL," );
    string p6("SERVER_DIR        VARCHAR(50) NOT NULL,");
    string p7("CLIENT_DIR        VARCHAR(50));");
    creator.exec( (p1+p2+p3+p4+p5+p6+p7).c_str() );
    db.close();
    return true;
}
bool Server::AddUser(string uID, string Password, string Server_Dir, string Client_Dir){
    if ( !db.isOpen() ) {
        db.open();
    }
    cout << " now adding user \n";
    //Note : Server_Dir is not know at all. Fetch it from createDirectory.
    Server_Dir = SERVER_DIRECTORY;
    Server_Dir += uID; //Assert : Creates the correct server directory.
    string myval = " VALUES('" + uID + "','" + Password + "','" + Server_Dir + "','" + Client_Dir + "');";
    QSqlQuery inserter;
    string p1("INSERT INTO " );
    string p2(TABLE_NAME);
    string p3(" (USERNAME,PASSWORD,SERVER_DIR,CLIENT_DIR) ");
    inserter.exec( (p1+p2+p3+myval).c_str());
    db.close();
    return true;
}
bool Server::DeleteUser(string uID) {
    if ( !db.isOpen() ) {
        db.open();
    }
    QSqlQuery deletor;
    string p1("DELETE FROM ");
    string p2(TABLE_NAME);
    string p3(" where USERNAME='");
    string p4("';");
    deletor.exec( (p1+p2+p3+uID+p4).c_str() );
    db.close();
    return true;
}

bool Server::UpdateDatabase( string uID, string Npassword){ //Change password stuff.
    if ( !db.isOpen() ) {
        db.open();
    }
    QSqlQuery deletor;
    string p1("UPDATE " );
    string p2(TABLE_NAME);
    string p3( " SET PASSWORD='");
    string p4("' where USERNAME='");
    string p5( "';");
    deletor.exec((p1+p2+p3+Npassword+p4+uID+p5).c_str());
    db.close();
    return true;
}

bool Server::fetchUserbyID(UserDetails &usr) {
    if ( !db.isOpen() ) {
        db.open();
    }
    QSqlQuery fetcher;
    string p1("SELECT USERNAME,PASSWORD,SERVER_DIR,CLIENT_DIR FROM ");
    string p2(TABLE_NAME);
    string p3(" where USERNAME='");
    string p4("';");
    fetcher.exec((p1 +p2 + p3 + usr.userID + p4).c_str());
    while ( fetcher.isSelect() && fetcher.next() ) {
        //usr.userID is unchanged.
        cout << "found a value for user\n";
        usr.password = fetcher.value(1).toString().toUtf8().constData();
        usr.serverDirectory = fetcher.value(2).toString().toUtf8().constData();
        usr.clientDirectory = fetcher.value(3).toString().toUtf8().constData();
        db.close();
        return true;
    }

    db.close();
    return false;
}

bool Server::authenticate(string userid, string passwd) {
    UserDetails usr;
        usr.userID = userid;
    if ( fetchUserbyID(usr) ) {
        cout << " fetched password is " << usr.password << " and read pw is " << passwd << "\n";
        return (usr.password == passwd);
    } else {
        return false;
    }
}

bool Server::authenticate( UserDetails& usr ) {
    string passwd = usr.password;
    if ( fetchUserbyID(usr) ) {
        cout << " fetched password is " << usr.password << " and read pw is " << passwd << "\n";
        return (usr.password == passwd);
    } else {
        return false;
    }
}


#endif
