#ifndef COMMENT_H
#define COMMENT_H
#include "user.h"
#include "location.h"
#include <QString>
using namespace std;
class User;

class Comment
{
public:
    User user;
    QString review;
    Comment(User user, QString review);
};

#endif // COMMENT_H
