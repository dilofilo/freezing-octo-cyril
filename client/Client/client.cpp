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
#include "logintoreg.cpp"

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
    this->handleEvent(LAUNCH);
}

bool Client::eventHandler( INSTRUCTION_TYPE instr ) { //Handle the InstructionData data appropriately.
    if (instr == PING_INSTR) {
        return this->handlePing(); //Nothing to handle, really.
    } else if ( instr == LAUNCH) {
        return this->launch();
    } else if ( instr == LOGIN_TO_CLIENT) {
        return this->unlaunch();
    } else if ( instr == LOGIN_TO_REGISTER) {
        return this->goToRegisterPage();
    } else if ( instr == REGISTER_TO_LOGIN_BACK) {
        return this->goBackToLoginPage();
    } else if ( instr == REGISTER_TO_LOGIN_REGISTER) {
        return this->handleRegistration();
    }else {
        //Assume exitting.
        this->exit();
    }
}

/*
 *##################### MINION FUNCTIONS FOLLOW #############
*/
void Client::exit() {
    std::string temp(EXIT_REQUEST);
    conn.writeToSocket( temp );
}
