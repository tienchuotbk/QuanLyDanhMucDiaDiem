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

        user.name = name.toString();
        user.age = age.toInt();
        user.phone = phone.toString();
        user.address = address.toString();


        ui->label_user_id->setText(QString::number(user.get_userid()));
        ui->label_username->setText(user.get_username());
        ui->input_name->setText(name.toString());
        ui->input_age->setText(age.toString());
        ui->input_phone->setText(phone.toString());
        ui->input_address->setText(address.toString());
    }
}

void changeinfor::on_btn_save_clicked()
{
    QString password = ui->input_password->text();
    QString name = ui->input_name->text();
    QString age = ui->input_age->text();
    QString phone = ui->input_phone->text();
    QString address = ui->input_address->text();
    QString newpass = ui->input_password->text();

    User& user = User::getInstance();

    if( ui->input_password->text().isEmpty()){
    }else{
        //REQ_CPAS{"id":1, "oldpassword": "123456", "newpassword": "1234567"}
        QString req = "REQ_CPAS{\"id\": "+QString::number(user.get_userid())+", \"oldpassword\": \""+user.get_password()+"\", \"newpassword\": \""+password+"\"}";
        qDebug() <<req;
        char *response = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
        qDebug() << response;
        user.set_password(password);
    }
    //REQ_CINF{"userId": 1, "name": "Tien Chuot", "age": 25, "phone": "0816553223", "address": "895 Minh Khai"}
    QString req = "REQ_CINF{\"userId\": "+QString::number(user.get_userid())+", \"name\": \""+name+"\", \"age\": "+age+", \"phone\": \""+phone+"\", \"address\": \""+address+"\"}";
    qDebug() <<req;
    char * response = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    qDebug() <<response;
    user.name = name;
    user.age = age.toInt();
    user.phone = phone;
    user.address = address;

    this->close();
}

