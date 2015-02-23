#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QMainWindow>


#include "../../common/instructions.h"
#include "../../common/communications.h" //does typedef int Socket.

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit RegisterPage(QWidget *parent = 0);
    RegisterPage(QMainWindow* client);
    RegisterPage(Socket& _csock);
    ~RegisterPage();
    
private:
    Socket csock;
    Ui::RegisterPage *ui;
};

#include "client.h" //Safe because forward declaration and header guards.
#endif // REGISTERPAGE_H
