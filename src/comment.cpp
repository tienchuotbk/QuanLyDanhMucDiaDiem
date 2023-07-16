#include "comment.h"
#include "ui_comment.h"
#include <QDebug>
#include "singleton.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "user.h"
#include <QString>
#include "friendinfo.h"

comment::comment(QString locationId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::comment)
{
    ui->setupUi(this);
    this->locationId = locationId;
    this->set_label();
}

comment::~comment()
{
    delete ui;
}

void comment::set_label(){
        QString req = "REQ_LOCA{\"locationId\": "+this->locationId+"}";
        qDebug() << req;
        char *jsonData = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
        qDebug() << jsonData;
        QVector<QString> values = {"ALL","School", "Coffe", "Restaurant", "Park", "Mall", "Market", "Hospital", "Others"};
        QByteArray jsonByteArray(jsonData);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByteArray);
        if (!jsonDoc.isNull()) {
               QJsonObject jsonObj = jsonDoc.object();
               // Kiểm tra giá trị "success"
                   QString username = jsonObj["createdUserName"].toString();
                   int id = jsonObj["createdUserId"].toInt();
                   int type = jsonObj["type"].toInt();
                   QString address = jsonObj["address"].toString();
                   QString locationName = jsonObj["locationName"].toString();
                    qDebug() << "id of this account: "+QString::number(id);
                   this->userId = QString::number(id);

                   ui->label_username->setText(username);
                   ui->label_id->setText(QString::number(id));
                   ui->label_type->setText(values.at(type));
                   ui->label_locationName->setText(locationName);
                   ui->label_address->setText(address);

                   QJsonArray ar = jsonObj["comment"].toArray();
                   User &user = User::getInstance();
                   foreach (const QJsonValue& item, ar) {
                       // Lấy thông tin
                       //"userId": 2, "userName": "Nguyen Ngoc Tu", "locationId": 5, "locationName": "Bach Mai", "type": 7, "locationAdd": "15 Giai Phong, Hai Ba Trung, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 4, "locationName": "Dong Xuan", "type": 6, "locationAdd": "Hang Buom, Hoan Kiem, Ha Noi"}, {"userId": 2, "userName": "Nguyen Ngoc Tu", "locationId": 3, "locationName": "Lau Phan", "type": 3, "locationAdd": "15 Pho Hue, Hai Ba Trung, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 2, "locationName": "Gongtea", "type": 2, "locationAdd": "23 Vu Trong Phung, Thanh Xuan, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 1, "locationName": "Dai hoc Bach Khoa Ha Noi", "type": 1, "locationAdd": "1 Dai Co Viet, Hai Ba Trung, Ha Noi"
                       QJsonObject itemObj = item.toObject();
                       int id = itemObj["id"].toInt();

                       QString name = itemObj["name"].toString();
                       QString comt = itemObj["content"].toString();
                       QString listItem;

                       // Thêm thông tin vào QListWidget
                       if(user.get_userid() == id){
                           listItem = QString("\nYou :%2").arg(
                                   comt);
                       }else{
                           listItem = QString("\n%1 :%2").arg(
                                   name, comt);
                       }
                       ui->listcomment->addItem(listItem);
                   }
                   //this->comts->show();
                  }
}

void comment::on_btn_comment_clicked()
{
    QString comt = ui->input_comment->text();
    QString item = QString("\nYou :%2").arg(comt);
    User &user = User::getInstance();
    ui->listcomment->addItem(item);
//PUT_RVIE{"userId": 1, "type": 2, "userName": "Van Tien", "locationId": 4, "content": "Rat dep"}
    QString req = "PUT_RVIE{\"userId\": "+QString::number(user.get_userid())+", \"type\": 2, \"userName\": \""+user.get_username()+"\", \"locationId\": "+this->locationId+", \"content\": \""+comt+"\"}";
    char *response = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    qDebug() << response;
}


void comment::on_btn_viewUser_clicked()
{
    friendinfo *friendi = new friendinfo(this->userId);
    friendi->exec();
    delete friendi;
}


void comment::on_pushButton_clicked()
{
    QString req = "GET_RECO{\"userId\": "+QString::number(User::getInstance().get_userid())+"}";
    char *response = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    qDebug() << response;
}

