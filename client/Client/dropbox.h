#ifndef DROPBOX_H
#define DROPBOX_H

#include <QMainWindow>

namespace Ui {
class DropBox;
}

class DropBox : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DropBox(QWidget *parent = 0);
    DropBox(QMainWindow* client);
    DropBox(Socket& _csock);
    ~DropBox();
    
private:
    Socket csock;
    Ui::DropBox *ui;
};

#endif // DROPBOX_H
