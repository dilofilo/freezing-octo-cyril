#ifndef LOGIN_TO_REG_CPP
#define LOGIN_TO_REG_CPP

#include "client.h"
void Client::goToRegisterPage() { //Login To Register.
    this->registerpage = new RegisterPage(this , csock);
    this->loginpage->hide();
    this->registerpage->show();
}

void Client::goBackToLoginPage() {

}

#endif
