#ifndef CLIENTDEFINITIONS_H
#define CLIENTDEFINITIONS_H
#define CLIENT_SIDE
#include <string>
#include <string.h>
#include "../../common/instructions.h" //includes UserDetails.
#include "../../common/communications.h"
//This enum is used to trigger events of the client.
enum INSTRUCTION_TYPE {
    // Page Navigation
    LAUNCH, //unused
    PING_INSTR, //Button for pinging.
    //CLIENT_TO_LOGIN, Same as LAUNCH
    LOGIN_TO_CLIENT, //Button called btn_back on login.ui
    LOGIN_TO_REGISTER, //Button for register on login.ui
    REGISTER_TO_LOGIN_BACK, //back button on register.
    REGISTER_TO_LOGIN_REGISTER, //Confirm Registration button on registration page.
    LOGIN_TO_MAIN, //login button
    MAIN_TO_LOGIN, //logout button

    //File Uploads and Downloads and Removes
    UPLOAD_FILE, //upload file button
    DOWNLOAD_FILE, //download file button
    SYNC, //synchronize button
    REMOVE_FILE, //remove file button
    REVERT, //Revert button
    FILE_SHARE, //share button
    FILE_UNSHARE // unshare button
};

struct InstructionData {
    INSTRUCTION_TYPE type;
    UserDetails user;
    std::string filename;
    UserDetails other_user;
    FILE_MODE filetype;
    //Add more as required.
};

#endif // CLIENTDEFINITIONS_H
