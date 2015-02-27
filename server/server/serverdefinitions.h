#ifndef SERVERDEFINITIONS_H
#define SERVERDEFINITIONS_H

enum EDIT_MODE { EDIT , NEW };

#define TEMPPREFIX "temp"
#define USERTABLE "USERFILES"
//#define SHAREDWITHTABLE "SHAREDWITH"
//#define SHAREDBYTABLE "SHAREDBY"
#define SHAREDTABLE "SHAREDFILES"
#define LOCAL_HOST "127.0.0.1"
#define TABLE_NAME "USERDB"
#define SERVER_DIRECTORY "MBD/Directories/"
#define DATABASE "ADMIN/Records.db"
    //This is the beginning for all user base directories.
#define MYFILES "myfiles.txt"
#define SHARED_WITH_ME "filesin.txt"
#define FILES_I_SHARED "filesout.txt"
#define TEMP "temp.txt"
#define ADMIN_ID "dilofilo"
#define ADMIN_PW "lolpw"
    //I wish the admin password could be secured in a better manner, but thats alright.
#endif // SERVERDEFINITIONS_H
