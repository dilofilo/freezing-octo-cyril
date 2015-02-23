#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>

#include "../../common/instructions.h"
#include "../../common/communications.h"

class Client;

namespace Ui {
class Client;
class LoginPage;
class Registerpage;
class DropBox;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LoginPage(QWidget *parent = 0);
    LoginPage(Client* _client , Socket& csock); //This is what I need. Afterall, I need backward and forward motion.
    ~LoginPage();
private slots:
    void on_btn_ping_clicked();

    void on_btn_back_clicked();

private:
    Socket csock;
    Client * client;
    Ui::LoginPage *ui;

    void backToClientPage();
};

#include "client.h" //Safe because forward declaraitons and header guards.
#endif // LOGINPAGE_H
