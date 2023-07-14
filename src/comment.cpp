#include "comment.h"
#include "user.h"

Comment::Comment(User user, QString review):user(user), review(review){
    this->user =  user;
    this->review = review;
}
