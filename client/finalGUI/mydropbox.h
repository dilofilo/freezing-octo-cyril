#ifndef MYDROPBOX_H
#define MYDROPBOX_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QtCore>
#include <QtGui>
#include <vector>
#include <QDirModel>
#include <QInputDialog>

namespace Ui {
class myDropBox;
}

class myDropBox : public QMainWindow
{
    Q_OBJECT
    void AddRoot(QString Name,const std::vector<QString> childName);
    void AddChild(QTreeWidgetItem *parent,QString Name);
public:
    explicit myDropBox(QWidget *parent = 0);
    ~myDropBox();
    
private slots:
    void on_btnMake_clicked();

    void on_btnDelete_clicked();

private:
    Ui::myDropBox *ui;
    QDirModel *model;
};

#endif // MYDROPBOX_H
