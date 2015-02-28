#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QMainWindow>

class Client;
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
    RegisterPage(Client* _client , Socket& _csock);
    ~RegisterPage();
    Ui::RegisterPage *ui;

private slots:
    void on_btn_registerConfirm_clicked();
    
    void on_btn_ping_clicked();

    void on_btn_back_clicked();

    void on_btn_browse_clicked();

    void on_txt_username_selectionChanged();

private:
    Socket csock;
    Client* client;
};

#include "client.h" //Safe because forward declaration and header guards.
#endif // REGISTERPAGE_H

