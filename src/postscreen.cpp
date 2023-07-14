#include "postscreen.h"
#include "ui_postscreen.h"
#include "location.h"
#include <QDebug>
#include "singleton.h"
#include "user.h"

class Location;
postscreen::postscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postscreen)
{
    ui->setupUi(this);
    Singleton::getInstance();
}

postscreen::~postscreen()
{
    delete ui;
}

void postscreen::collect_input(){
    this->address = ui->input_address->toPlainText();
    this->location_name = ui->input_name->text();
    this->type = ui->combo_type->currentIndex()+1;
}

void postscreen::on_btn_post_clicked()
{
    this->collect_input();
    User&user = User::getInstance();
    QString req = "PUT_SHLC{\"userId\": "+QString::number(user.get_userid())+"\", \"type\": 1, \"userName\": \""+user.get_username()+"\", \"name\": \""+this->location_name
            +"\", \"type\": "+QString::number(this->type)+", \"address\": \""+this->address+"\"}";
    char *jsonData = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    qDebug()<< jsonData;
}

