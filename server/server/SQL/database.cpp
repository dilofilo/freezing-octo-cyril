#ifndef USERDATABASE_CPP
#define USERDATABASE_CPP
/*
This file handles with reading databases and reading user's file directory etc.

TODO list.
*/

#include "server.h"
#include <string>
#include "sqlite3.h"

static int Server::callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

bool Server::CreateHashTable(void *NotUsed, int argc, char **argv, char **azColName){
//    int i;
//    for(i=0; i<argc; i++){
//       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }

    // Insert azColName[0] and azColName[1] in the hash table

    userDetails[azColName[0]] = azColName[1];

    return 0;
 }

bool Server::main_CreateDatabase(){

    sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("Records.db", &db);        // Name of the Databas is Records.db

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return 0;
   }else{
      fprintf(stderr, "Opened database successfully\n");
      return 1;
   }
   sqlite3_close(db);
}

bool Server::CreateTable(){

    sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
    char *sql;

    /* Open database */
    rc = sqlite3_open("Records.db", &db);
    if( rc ){
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       exit(0);
    }else{
       fprintf(stdout, "Opened database successfully\n");
    }

    /* Create SQL statement */

    sql = "CREATE TABLE SERVER_RECORDS("  \
          "USERNAME         VARCHAR(50) PRIMARY KEY NOT NULL," \
          "PASSWORD         VARCHAR(50) NOT NULL," \
          "SERVER_DIR        VARCHAR(50) NOT NULL," \
          "CLIENT_DIR        VARCHAR(50) NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       return 0;
    }else{
       fprintf(stdout, "Table created successfully\n");
       return 1;
    }
    sqlite3_close(db);

}

bool Server::AddUser(string uID, string Password, string Server_Dir, string Client_Dir){

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("Records.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
   string myval = "VALUES(" + uID + "," + Password + "," + Server_Dir + "," + Client_Dir + ");";

   /* Create SQL statement */
   string sqlTemp = "INSERT INTO SERVER_RECORDS (USERNAME,PASSWORD,SERVER_DIR,CLIENT_DIR) " + myval;
  sql = sqlTemp.c_str();

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
      userDetails[uID] = Password;
      sqlite3_close(db);
      return 1;
   }
   sqlite3_close(db);
   return 0;
}

bool Server::DeleteUser(string uID){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("Records.db", &db);
    if( rc ){
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       exit(0);
    }else{
       fprintf(stderr, "Opened database successfully\n");
    }

    /* Create merged SQL statement */

    string del = "DELETE from SERVER_RECORDS where USERNAME=" + uID + ";" + "SELECT * from COMPANY";    // delete the user and print the table
     sql = del.c_str();

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    }else{
       fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}

bool Server::UpdateDatabase(UserDetails user , EDIT_MODE mode) {
    // ????????????????????????????????
}


bool Server::main_ReadDatabase() { //The structure of the reading.
    if( main_GetAdmin() ) {
        if (main_ReadUsers()) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Server::main_CreateDictionary(){

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("Records.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * from SERVER_RECORDS";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, CreateHashTable, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);

}

bool Server::main_GetAdmin() { //Modify this function accordingly.
    return true;
}
bool Server::main_ReadUsers() { //Modify this function accordingly.
    return true;
}

bool Server::authenticate(std::string userid , std::string passwd) {

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;

    int rc = sqlite3_open("Records.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT USERNAME, PASSWORD FROM SERVER_RECORDS WHERE USERNAME = @USER";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

    int idx = sqlite3_bind_parameter_index(res, "@USER");
    sqlite3_bind_int(res, idx, userid);

    } else {

        fprintf(stderr, "Username Does Not exist. %s\n", sqlite3_errmsg(db));
        return 0;
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {
        string temp(sqlite3_column_text(res, 1));
        if(temp.compare(passwd) == 0){
            sqlite3_finalize(res);
            sqlite3_close(db);
            return 1;
        }

        return 0;

    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    
    
    return false;
}

#endif
