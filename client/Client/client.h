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
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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
    //User
    UserDetails user;

    bool eventHandler( INSTRUCTION_TYPE instr ); //This is the handler.
        InstructionData data; //This data conveys data you might need.
        bool handlePing(); //clientping
        void launch();   //launcher
        void unlaunch(); //launcher
        void goToRegisterPage(); // L_TO_R
        void goBackToLoginPage(); // L_TO_R
        bool handleRegistration(); // Upon clicking registration.
            //bool registrationRequest( std::string _user , std::string _pw , std::string _dir);
        bool handleLogin(); //userLogin.cpp
            //bool sendLogin();
        bool handleLogout(); //userLogin.cpp
        bool handleUpload(); //fileUpload.cpp
        bool handleDownload(); //fileDownload.cpp
        //bool handleDownloadAll();
        bool handleRemove(); //fileRemove.cpp
        bool handleSync(); //sync.cpp
        bool handleRevert(); //revert.cpp
        bool handleShare(); //share.cpp
        bool addToFileLog_shared(string uid, string fname, string owner);
        bool handleUnshare(); //share.cpp
        bool handleSearch(); //search.cpp
        void handleExit(); // client.cpp
        void showMain();
        bool populateSyncFileList(); //sync.cpp

private slots:
    void on_btn_launch_clicked();

private:

    SSL_CTX *clientCTX;
    SSL *sslcsock;
    //Socket creation things.
    Socket csock;
    struct sockaddr_in serverAddress, clientAddress;
    //struct hostent* server_entity; Not necessary.
    std::string serverAddress_string;


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

        //Auxillary Functions.
        //Login, Registration
        bool registrationRequest( std::string _user , std::string _pw , std::string _dir);
        bool sendLogin( std::string& _user , std::string& _pw , std::string& _dir);

        //Directory Handling.
        bool handleDirectory(); //Handles the client side directory and file system.

        //File Upload
        bool uploadNewFile();
        bool uploadDiffFile();
        bool uploadRemoteDiff();
        string processFileName( string fname );

        bool createFileLog(std::string uid , std::string clidir); //Creates the file
        bool addToFileLog(std::string uid , std::string fname , std::string path , int version); //Ensures that there are no duplicates.
        string findFilePath(string pfn); // Handles things.

        void getServerFiles_login();
        void populateFileData_login_shared(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string> fo); //Reads from files and puts it into this.
        void populateFileData_login_normal(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string> fo); //Reads from files and puts it into this.

        //File Download.

        //File Remove - from server directory.

        //File Sync - Need a history file.

        //File Share.

        //File Revert
};

#endif // CLIENT_H
