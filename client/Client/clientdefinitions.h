#ifndef CLIENTDEFINITIONS_H
#define CLIENTDEFINITIONS_H
#define CLIENT_SIDE
#include <string>
#include <string.h>
//This enum is used to trigger events of the client.
enum INSTRUCTION_TYPE {
    // Page Navigation
    LAUNCH, //unused
    PING_INSTR,
    //CLIENT_TO_LOGIN, Same as LAUNCH
    LOGIN_TO_CLIENT,
    LOGIN_TO_REGISTER,
    REGISTER_TO_LOGIN_BACK,
    REGISTER_TO_LOGIN_REGISTER,
    LOGIN_TO_MAIN,
    MAIN_TO_LOGIN,

    //File Uploads and Downloads and Removes
    UPLOAD_FILE,
    DOWNLOAD_FILE,
    SYNC,
    REMOVE_FILE
};

struct InstructionData {
    INSTRUCTION_TYPE type;
    UserDetails user;
    std::string filename;
    UserDetails other_user;
    //Add more as required.
};

#endif // CLIENTDEFINITIONS_H
