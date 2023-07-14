#ifndef NEWFEED_H
#define NEWFEED_H
#include "post.h"
#include "list"
using namespace std;


class Newfeed
{
public:
    list<Post> feed;
    void add_post(Post post);
    list<Post> get_post();
};

#endif // NEWFEED_H
