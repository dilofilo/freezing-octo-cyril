#ifndef LOGIN_TO_REG_CPP
#define LOGIN_TO_REG_CPP

#include "client.h"
void Client::goToRegisterPage() { //Login To Register.
    this->registerpage = new RegisterPage(this , csock);
    this->loginpage->hide();
    this->registerpage->show();
    //Complete?
}

void Client::goBackToLoginPage() {
    delete this->registerpage;
    this->loginpage->show();
    //Done.
}

#endif
