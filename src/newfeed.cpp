#include "newfeed.h"

void Newfeed::add_post(Post post){
    this->feed.push_front(post);
}

list<Post> Newfeed::get_post(){
    return this->feed;
}
