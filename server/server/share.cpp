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
    conn.readFromSocket(owner);

    //Need to write the user.
    QSqlQuery existance;
    string findhim = "SELECT FROM ";
        findhim += TABLE_NAME;
        findhim += " WHERE USERNAME='" + owner + "';";

    db.open();
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
        query += " (FILENAME , USER , OWNER) ";
        query += " VALUES('" + filename +"' , '" + user.userID + "' , '" + owner + "');";
    //Send back the log file.
    QString qquery = QString::fromStdString(query);
    share.exec(qquery);
    db.close();
    handleSync(user.userID);
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
    conn.readFromSocket(owner);

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
        query += " WHERE FILENAME='" + filename + "' AND USER='" + user.userID + "' AND OWNER='" + owner + "';";
    //Send back the log file.
    QString qquery = QString::fromStdString(query);
    unshare.exec(qquery);
    //Send back the log file.
    db.close();
    handleSync(user.userID);
    return true;
}

#endif
