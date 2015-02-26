#ifndef LOGIN_TO_REG_CPP
#define LOGIN_TO_REG_CPP

#include "client.h"
void Client::goToRegisterPage() { //Login To Register.
    this->loginpage->hide();
    this->registerpage->show();
    //Complete?
}

void Client::goBackToLoginPage() {
    this->registerpage->hide();
    this->loginpage->show();
    //Done.
}

#endif
