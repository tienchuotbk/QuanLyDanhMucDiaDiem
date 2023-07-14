#include "changeinfor.h"
#include "ui_changeinfor.h"
#include "user.h"
#include <QMessageBox>
#include "singleton.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <mainwindow.h>

changeinfor::changeinfor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeinfor)
{
    ui->setupUi(this);
    this->get_infor();
}

changeinfor::~changeinfor()
{
    delete ui;
}

void changeinfor::get_infor(){
    User& user = User::getInstance();
    QString data = "{\"username\": \""+user.get_username()+"\", \"password\": \""+user.get_password()+"\"}";
    QString request = "REQ_LOGI"+data;
    char *req = request.toUtf8().data();
    qDebug() <<req;

    char *jsonString = Singleton::getInstance().sendandrecieve(req);
    qDebug() <<jsonString;
    //QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray(jsonString));
    QJsonObject jsonObject = jsonDocument.object();
    QJsonValue statusValue = jsonObject.value("status");
    if (statusValue.isDouble()) {
        int status = statusValue.toInt();

        qDebug() << "status:" << status;
    } else {
        qDebug() << "Invalid value type for status.";
    }
    if(statusValue == 1){
        qDebug() <<"Get information!";
        QJsonValue name = jsonObject.value("name");
        QJsonValue age = jsonObject.value("age");
        QJsonValue phone = jsonObject.value("phone");
        QJsonValue address = jsonObject.value("address");

        ui->label_user_id->setText(QString::number(user.get_userid()));
        ui->label_username->setText(user.get_username());
        ui->label_name->setText(name.toString());
        ui->label_age->setText(age.toString());
        ui->label_phone->setText(phone.toString());
        ui->label_address->setText(address.toString());
    }
}

void changeinfor::on_btn_save_clicked()
{
    QString newpass = ui->input_password->text();
    if(newpass.isNull()){
        QMessageBox::warning(this,"Change Password","Your new password is invalid./nChange password failed!");
    }else{
        User& user = User::getInstance();
        QString req = "REQ_CPAS{\"id\":"+QString::number(user.get_userid())+", \"oldpassword\": \""+user.get_password()+"\", \"newpassword\": \""+newpass+"\"}";
        char *jsonData = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
        qDebug() << jsonData;
        user.set_password(newpass);
    }
    this->close();
}

