#ifndef SHARE_CPP
#define SHARE_CPP

#include "server.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"
#include <QSql>

bool Server::handleShare() {
    //Send a continue.
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);

    //Read the filename.
    std::string filename;
    conn.readFromSocket(filename);
    //write a continue
    conn.writeToSocket(cont);
    //Read the owner.
    std::string owner;
    conn.readFromSocket(owner); //Other user.
    cout << "sharing file="<< filename << " for user="<< user.userID << " to="<<owner<< "\n";
    db.open();
    //Need to write the user.
    QSqlQuery existance;
    string findhim = "SELECT FROM ";
        findhim += TABLE_NAME;
        findhim += " WHERE USERNAME='" + owner + "';";

        cout << "###executing select user="<< findhim << "\n";
    QString qfindhim = QString::fromStdString(findhim);
    existance.exec(qfindhim);
    if (existance.next()) {
        std::string acc(SHARE_ACCEPTED);
        conn.writeToSocket(acc);
    } else {
        std::string rej(SHARE_REJECTED);
        conn.writeToSocket(rej);
    }
    conn.readFromSocket(cont);
    //Update the database.
    QSqlQuery share;
    //TODO
    string query("INSERT INTO ");
        query += SHAREDTABLE;
        query += " (FILENAME,USER,OWNER)"; //User is the guy who has access to the file, Owner is the guy who has write rights.
        query += " VALUES('" + filename + "','" + owner + "','" + user.userID + "');"; //"owner" here is the OTHER USER.
    //Send back the log file.
    cout << "###executing query=" << query << "\n";
    QString qquery = QString::fromStdString(query);
    share.exec(qquery);

    db.close();
    cout << "about to handly syncin share()\n";
    handleSync(user.userID);
    cout << "done handlesync share() \n";
    return true;
}

bool Server::handleUnshare() {
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);

    //Read the filename.
    std::string filename;
    conn.readFromSocket(filename);
    //write a continue
    conn.writeToSocket(cont);
    //Read the owner.
    std::string owner;
    conn.readFromSocket(owner);//Owner is the other yser.

    //Check if unshare request is valid.
    db.open();
    QSqlQuery existance;
    string findhim = "SELECT FROM ";
        findhim += TABLE_NAME;
        findhim += " WHERE USERNAME='" + owner + "';";

    QString qfindhim = QString::fromStdString(findhim);
    existance.exec(qfindhim);
    if (existance.next()) {
        std::string acc(UNSHARE_ACCEPTED);
        conn.writeToSocket(acc);
    } else {
        std::string rej(UNSHARE_REJECTED);
        conn.writeToSocket(rej);
    }

    conn.readFromSocket(cont);
    //Update the database.
    QSqlQuery unshare;
    string query("DELETE FROM ");
        query += SHAREDTABLE;
        query += " WHERE FILENAME='" + filename + "' AND USER='" + owner + "' AND OWNER='" + user.userID + "';";
    //Send back the log file.
    QString qquery = QString::fromStdString(query);
    unshare.exec(qquery);
    //Send back the log file.
    db.close();
    handleSync(user.userID);
    return true;
}

#endif
