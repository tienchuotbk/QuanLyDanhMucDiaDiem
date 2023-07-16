#include "friend.h"
#include "ui_friend.h"

Friend::Friend(const QString& id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Friend)
{
    ui->setupUi(this);
}

Friend::~FriendDialog()
{
    delete ui;
}
