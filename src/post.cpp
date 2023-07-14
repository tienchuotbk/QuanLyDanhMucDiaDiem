#include "post.h"

Post::Post() {
    user = nullptr;
    location = nullptr;
}

Post::Post(User* user, Location* location)
    : user(user), location(location) {
    // Constructor implementation
}
