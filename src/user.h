#ifndef USER_H
#define USER_H
#include "location.h"
#include <QList>
#include <QString>
using namespace std;

class Location;

class User
{
public:
    static User& getInstance();
    void set_user(int user_id, QString username,QString password);
    void add_location(const Location& location);
    QList<Location>& get_location();
    int get_userid();
    QString get_username();
    QString get_password();
    void set_password(QString newpass);
    QString name;
    int age;
    QString phone;
    QString address;
private:
    int user_id;
    QString username;
    QString password;

    User();
    User(const User&) = delete;
    User& operator=(const User&) = delete;
};

#endif // USER_H
