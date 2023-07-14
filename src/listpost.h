#ifndef LISTPOST_H
#define LISTPOST_H
#include <QList>
#include <post.h>

class Listpost{
public:
    static Listpost& getInstance();

    QList<Post> getList() const;
    void setList(const QList<Post>& list);

private:
    QList<Post> m_list;

    Listpost() {}
    Listpost(const Listpost&) = delete;
    Listpost& operator=(const Listpost&) = delete;
};

#endif // LISTPOST_H
