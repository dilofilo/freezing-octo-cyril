#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>


namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    
private slots:
    void on_btnRegister_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
