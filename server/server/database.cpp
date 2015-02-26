#ifndef USERDATABASE_CPP
#define USERDATABASE_CPP
/*
This file handles with reading databases and reading user's file directory etc.

TODO list.
*/

#include "server.h"
#include "serverdefinitions.h"
#include <string>
#include "SQL/sqlite3.h"
#include <sstream>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int CreateHashTable(void *NotUsed, int argc, char **argv, char **azColName ){
    // Insert azColName[0] and azColName[1] in the hash table

    std::string u(azColName[0]); //username
    std::string p(azColName[1]); //password
    //    std::pair<std::string , UserDetails> us(u,p);
    userDetails[u] = p; //.insert(us);   // Check if it works.
    return 0;
 }

bool Server::main_CreateDatabase(){

    sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("DATABASE", &db);        // Name of the Database is DATABASE

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return 0;
   }else{
      fprintf(stderr, "Opened database successfully\n");
      return 1;
   }
   sqlite3_close(db);
}

bool CreateTable(){

    sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
    char *sql;

    /* Open database */
    rc = sqlite3_open(DATABASE, &db);
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
   rc = sqlite3_open("DATABASE", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
   string myval = "VALUES(" + uID + "," + Password + "," + Server_Dir + "," + Client_Dir + ");";

   /* Create SQL statement */
   string sqlTemp = "INSERT INTO SERVER_RECORDS (USERNAME,PASSWORD,SERVER_DIR,CLIENT_DIR) " + myval;
   sql = (char*)malloc(sizeof(char)*(sqlTemp.size()));
   sqlTemp.copy(sql , sqlTemp.size()); //Valid copy. c_str returns a const char*, not a char*

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
      userDetails[uID] = Password;
      sqlite3_close(db);
      free(sql);
      return 1;
   }
   sqlite3_close(db);
   free(sql);
   return 0;
}

bool Server::DeleteUser(string uID){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("DATABASE", &db);
    if( rc ){
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       exit(0);
    }else{
       fprintf(stderr, "Opened database successfully\n");
    }

    /* Create merged SQL statement */

    string del = "DELETE from SERVER_RECORDS where USERNAME=" + uID + ";" + "SELECT * from COMPANY";    // delete the user and print the table
    sql = (char*)malloc(sizeof(char)*(del.size()));
    del.copy(sql , del.size()); //Valid copy. c_str returns a const char*, not a char*

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    }else{
       fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
    free(sql);
}

bool UpdateDatabase( string uID, string Npassword){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("DATABASE", &db);
    if( rc ){
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       exit(0);
    }else{
       fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */

    string tempsql = "UPDATE RECORDS SET PASSWORD =" + Npassword + "WHERE ID =" + uID + ";";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, tempsql.c_str(), CreateHashTable, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    }else{
       fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);


}

bool Server::fetchUserbyID( UserDetails& temp ){

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;

    int rc = sqlite3_open("DATABASE", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    char *sql;
    string query = "SELECT USERNAME, FROM SERVER_RECORDS WHERE USERNAME =" + userid + ";";

    sqlite3_stmt *statement;


    if ( sqlite3_prepare( DATABASE, query.c_str(), -1, &statement, 0 ) == SQLITE_OK )
       {
           int ctotal = sqlite3_column_count(statement);
           int res = 0;
           int count = 0;
           while ( 1 )
           {
               res = sqlite3_step(statement);

               if ( res == SQLITE_ROW )
               {
                   count++
               }

               if ( res == SQLITE_DONE || res==SQLITE_ERROR)
               {
                   break;
               }
           }

           if(count == 0 ){
               cout<<"Authenticated"<<endl;
               sqlite3_finalize(res);
               sqlite3_close(db);
               return true;
           }
       }


    sqlite3_finalize(res);
    sqlite3_close(db);
    return false;

}



bool Server::main_CreateDictionary(){

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("DATABASE", &db);
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

bool Server::main_ReadUsers() { //Modify this function accordingly.
    return true;
}

bool Server::authenticate(std::string userid , std::string passwd) {

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;

    int rc = sqlite3_open("DATABASE", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    char *sql;
    string query = "SELECT USERNAME, PASSWORD FROM SERVER_RECORDS WHERE USERNAME =" + userid + "AND PASSWORD = " + passwd + ";";

    sqlite3_stmt *statement;


    if ( sqlite3_prepare( DATABASE, query.c_str(), -1, &statement, 0 ) == SQLITE_OK )
       {
           int ctotal = sqlite3_column_count(statement);
           int res = 0;
           int count = 0;
           while ( 1 )
           {
               res = sqlite3_step(statement);

               if ( res == SQLITE_ROW )
               {
                   count++
               }

               if ( res == SQLITE_DONE || res==SQLITE_ERROR)
               {
                   break;
               }
           }

           if(count ==1 ){
               cout<<"Authenticated"<<endl;
               sqlite3_finalize(res);
               sqlite3_close(db);
               return true;
           }
       }


    sqlite3_finalize(res);
    sqlite3_close(db);
    return false;
}

#endif
