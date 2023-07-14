#include "user.h"
#include "location.h"
#include <QList>
#include <QDebug>

User::User(){
}

User& User::getInstance() {
    static User instance;
    return instance;
}

void User::set_user(int user_id, QString username, QString password){
    this->user_id = user_id;
    this->username = username;
    this->password = password;
    qDebug() << "insert success!";
}

int User::get_userid(){
    return this->user_id;
}

QString User::get_username(){
    return this->username;
}

QString User::get_password(){
    return this->password;
}

void User::set_password(QString newpass){this->password = newpass;}
