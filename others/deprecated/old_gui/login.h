#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <mydropbox.h>
#include "register.h"
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    
private slots:
    void on_btnSignIn_clicked();

    void on_btnRegister_clicked();

private:
    Ui::Login *ui;
    myDropBox *dropBox;
    Register *reg;
};

#endif // LOGIN_H
