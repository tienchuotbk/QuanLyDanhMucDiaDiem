#ifndef POST_H
#define POST_H
#include "user.h"
#include "location.h"

struct Post{
    User *user;
    Location *location;

    Post():user(),location(){};
};

#endif // POST_H
