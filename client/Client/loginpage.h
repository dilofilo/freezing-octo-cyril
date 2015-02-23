#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>

#include "../../common/instructions.h"
#include "../../common/communications.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LoginPage(QWidget *parent = 0);
    LoginPage(QMainWindow *client);
    Loginpage(Socket& _csock);
    ~LoginPage();
    Socket csock;
private slots:
    void on_btn_ping_clicked();

private:
    Socket csock;
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
