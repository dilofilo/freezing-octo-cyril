#ifndef CLIENT_H
#define CLIENT_H
using namespace std;
#include <QMainWindow>
//Connectivity Stuff
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

//Instructions and utility.
#include "../../common/instructions.h"
#include "../../common/communications.h" //does typedef int Socket.
#include "clientdefinitions.h" //Contains the definitions used for instruction handling.

//Client related files.
#include "loginpage.h"
#include "registerpage.h"
#include "dropbox.h"

namespace Ui {
class Client;
class LoginPage;
class RegisterPage;
class DropBox;
}
#ifndef CLIENT_SIDE
#define CLIENT_SIDE
#endif
class Client : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    //Event Handler.
    bool eventHandler( INSTRUCTION_TYPE instr ); //This is the handler.
        InstructionData data; //This data conveys data you might need.
        bool handlePing(); //clientping
        void launch();   //launcher
        void unlaunch(); //launcher
        void goToRegisterPage(); // L_TO_R
        void goBackToLoginPage(); // L_TO_R
        bool handleRegistration(); // Upon clicking registration.
        bool registrationRequest( std::string _user , std::string _pw , std::string _dir);
        bool handleLogin(); //userLogin.cpp
        bool handleLogout(); //userLogin.cpp
        bool handleUpload(); //fileUpload.cpp
        bool handleDownload(); //fileDownload.cpp
        bool handleRemove(); //fileRemove.cpp
        bool handleSync(); //sync.cpp
        bool handleRevert(); //revert.cpp
        bool handleShare(); //share.cpp
    //Adverse
    void exit();
private slots:
    void on_btn_launch_clicked();

private:
    //Socket creation things.
    Socket csock;
    struct sockaddr_in serverAddress, clientAddress;
    //struct hostent* server_entity; Not necessary.
    std::string serverAddress_string;

    //User
    UserDetails user;

    //UI Related object pointers. To be initialized upon connection.
    Ui::Client *ui; //Disabled after creation
    LoginPage *loginpage; //Show first.
    RegisterPage *registerpage; //Shown if registration is clicked.
    DropBox *dropboxpage; //Show after successful login.

    //Communications Object
    Communications conn; // following that old PHP-SQL stile maen. \_|_/
    //Connection functions.
    bool prepareSocket(std::string serveraddress);


        //Open next page functions.
        bool createPages();
        //Login pages
        void showLoginPage();
        //Main pages.


};

#endif // CLIENT_H
