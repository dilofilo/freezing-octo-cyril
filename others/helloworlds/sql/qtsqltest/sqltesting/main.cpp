#include <QCoreApplication>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //QSQLITE is the driver.
    db.setHostName("127.0.0.1");
    db.setDatabaseName("../db/dbname.db");
    db.setUserName("admin");
    db.setPassword("lol");
    bool ok = db.open(); //Opens succesfully.
    cout << ok << " and isOpen " << db.isOpen() <<"\n";
    db.close();
    cout << ok << " and isOpen " << db.isOpen() <<"\n";
    db.open();
    cout << ok << " and isOpen " << db.isOpen() <<"\n";
    //opened the the db.

    QSqlQuery q1;
    q1.exec(" SELECT PASSWORD FROM TEST_TABLE WHERE NAME=\'haroun\'");
    while(q1.next()) {
       QString name = q1.value(0).toString();
       cout << name.toUtf8().constData() << "\n";
    }
    return a.exec();
}
