#ifndef FRIEND_H
#define FRIEND_H
#include "user.h"
#include "list"
using namespace std;

class FriendList {
public:
    list<User> friends;
    void add_friend(User user);
private:
};

#endif // FRIEND_H
