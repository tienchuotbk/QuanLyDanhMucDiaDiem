#include "listpost.h"

Listpost& Listpost::getInstance() {
    static Listpost instance;
    return instance;
}

QList<Post> Listpost::getList() const {
    return m_list;
}

void Listpost::setList(const QList<Post>& list) {
    m_list = list;
}
