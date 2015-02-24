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
#include "userRegistration.cpp"

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
    if (instr == PING_INSTR) {
        return this->handlePing(); //Nothing to handle, really.
    } else if ( instr == LAUNCH) {
        this->launch();
    } else if ( instr == LOGIN_TO_CLIENT) {
        this->unlaunch();
    } else if ( instr == LOGIN_TO_REGISTER) {
        this->goToRegisterPage();
    } else if ( instr == REGISTER_TO_LOGIN_BACK) {
        this->goBackToLoginPage();
    } else if ( instr == REGISTER_TO_LOGIN_REGISTER) {
        this->handleRegistration();
    } else if ( instr == REGISTER_TO_LOGIN_REGISTER) {
    } else {
        //Assume exitting.
        this->exit();
    }
}

/*
 *##################### MINION FUNCTIONS FOLLOW #############
*/

bool Client::handleRegistration() {
    //Given user name and password to database functions.
    return false;
}


void Client::exit() {
    std::string temp(EXIT_REQUEST);
    conn.writeToSocket( temp );
}
#endif
