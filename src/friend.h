#ifndef FRIEND_H
#define FRIEND_H
#include <QString>
#include <QDialog>

namespace Ui {
class Friend;
}

class Friend : public QDialog
{
    Q_OBJECT

public:
    explicit Friend(QString& id,QWidget *parent = nullptr);
    ~Friend();

private:
    Ui::Friend *ui;
};

#endif // FRIEND_H
