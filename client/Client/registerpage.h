#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QMainWindow>

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

#endif // REGISTERPAGE_H
