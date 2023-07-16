#include "friendinfo.h"
#include "ui_friendinfo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "singleton.h"
#include <QDebug>
#include "user.h"
#include <QMessageBox>

friendinfo::friendinfo(QString &id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::friendinfo)
{
    ui->setupUi(this);
    this->id = id;
    this->set_infor();
}

friendinfo::~friendinfo()
{
    delete ui;
}

void friendinfo::set_infor(){
    QString req = "GET_USER{\"userId\": "+this->id+"}";
    qDebug() << req;
    char *jsonData = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    qDebug() << jsonData;

    QByteArray jsonByteArray(jsonData);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByteArray);
    if (!jsonDoc.isNull()) {
           QJsonObject jsonObj = jsonDoc.object();
           // Kiểm tra giá trị "success"
           if (jsonObj["success"].toInt() == 1) {
               QString name = jsonObj["name"].toString();
               int age = jsonObj["age"].toInt();
               QString phone = jsonObj["phone"].toString();
               QString address = jsonObj["address"].toString();

               ui->label_user_id->setText(this->id);
               ui->label_name->setText(name);
               ui->label_age->setText(QString::number(age));
               ui->label_phone->setText(phone);
               ui->label_address->setText(address);
           }else qDebug() << "success = 0";
    }
}

void friendinfo::on_btn_follow_clicked()
{
    QString content = "{\"userId\": "+QString::number(User::getInstance().get_userid())+", \"friendId\": "+this->id+"}";
    QString follow = "REQ_FOLW"+content;
    qDebug() <<follow;
    char *jsonData = Singleton::getInstance().sendandrecieve(follow.toUtf8().data());
    qDebug() << jsonData;
    QByteArray jsonByteArray(jsonData);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByteArray);
    if (!jsonDoc.isNull()) {
           QJsonObject jsonObj = jsonDoc.object();
           // Kiểm tra giá trị "success"
           if (jsonObj["success"].toInt() == 1) {
               qDebug() << jsonObj["success"].toString();
               QMessageBox::information(this,"Follow success", "You follow this user success");
    }
}
}

