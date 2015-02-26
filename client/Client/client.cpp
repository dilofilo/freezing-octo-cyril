#ifndef CLIENT_CPP
#define CLIENT_CPP
#include "client.h"
#include "ui_client.h"




//UNNECESSARY INCLUDES. REMOVE SOON.
#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include "arpa/inet.h"
#include <iostream>
#include "../../common/instructions.h"
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <QLineEdit>
#include <QMessageBox>

#include "clientping.cpp"
#include "launcher.cpp" // Also contains unlauncher.
#include "logintoreg.cpp" //
#include "userRegistration.cpp" //handleRegistration()
#include "userLogin.cpp" // handleLogin();
Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    //Assert : Presently, the client wants the IP Address.
}

Client::~Client()
{
    ::close(csock);
    delete ui;
}

void Client::on_btn_launch_clicked()
{
    this->eventHandler(LAUNCH);
}

bool Client::eventHandler( INSTRUCTION_TYPE instr ) { //Handle the InstructionData data appropriately.
    if (instr == PING_INSTR) {// to server
        return this->handlePing();
    } else if ( instr == LAUNCH) { // internal, except for connection
        this->launch(); //Done.
    } else if ( instr == LOGIN_TO_CLIENT) { //internal
        this->unlaunch(); //Done.
    } else if ( instr == LOGIN_TO_REGISTER) { //internal
        this->goToRegisterPage();
    } else if ( instr == REGISTER_TO_LOGIN_BACK) { //internal
        this->goBackToLoginPage(); //Done.
    } else if ( instr == REGISTER_TO_LOGIN_REGISTER) { //to server
        this->handleRegistration(); //Done. Need to write server side
    } else if ( instr == LOGIN_TO_MAIN) { //to server
        this->handleLogin(); //Done. Need to write server side.
    } else if ( instr == MAIN_TO_LOGIN) { //to server
        this->handleLogout(); // Need to link GUI click to the event
    } else if ( instr == UPLOAD_FILE) { //to server
        this->handleUpload(); //Done. Need to write the communications and server side equivalent.
    } else if ( instr == DOWNLOAD_FILE) { //to server
        this->handleDownload();
    } else if ( instr == REMOVE_FILE) { //to server
        this->handleRemove();
    } else if ( instr == SYNC) { //to server - retrieves dates and decides. Works only for files which have been uploaded at least once.
        this->handleSync();
    } else if ( instr == REVERT) { //to server
        this->handleRevert();
    } else if ( instr == FILE_SHARE) { //to server
        this->handleShare();
    } else if ( instr == FILE_UNSHARE ) {
        this->handleUnshare();
    } else if ( instr == FILE_SEARCH ) {
        this->handleSearch();
    } else if ( instr == MAIN_TO_DESKTOP ) {//have you handled this already?? its for exiting
               this->handleExit();
    } else { // to server
        //Assume exitting.
        this->handleExit();
    }
}

/*
 *##################### MINION FUNCTIONS FOLLOW #############
*/


void Client::handleExit() {
    std::string temp(EXIT_REQUEST);
    conn.writeToSocket( temp );
    ::close(csock);
}
#endif
