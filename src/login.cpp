#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <mainwindow.h>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    Singleton::getInstance();
    User::getInstance();
    //connect(ui->btn_login, &QPushButton::clicked, this, &login::openMainWindow);
}

login::~login()
{
    delete ui;
}

void login::openMainWindow()
{
    qDebug() <<" Open mainwindow";
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
}

void login::get_input(){
    this->username = ui->input_user->text();
    this->password = ui->input_password->text();
    this->data = "{\"username\": \""+this->username+"\", \"password\": \""+this->password+"\"}";
    qDebug() << this->data;
    ui->input_user->clear();
    ui->input_password->clear();
}

void login::on_btn_register_clicked()
{
    this->get_input();
    //REQ_REGI{"username": "chuot", "password": "123456"}
    QString request = "REQ_REGI"+this->data;
    char* req = request.toUtf8().data();
    qDebug() << req;
    char*jsonString = Singleton::getInstance().sendandrecieve(req);
    qDebug() << jsonString;

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray(jsonString), &parseError);
    QJsonObject jsonObject = jsonDocument.object();
       QJsonValue statusValue = jsonObject.value("status");
       if (statusValue.isDouble()) {
           int status = statusValue.toInt();

           qDebug() << "status:" << status;
       } else {
           qDebug() << "Invalid value type for status.";
       }
    if(statusValue == 1){
       QMessageBox::information(this, "Register","Register successs!");
       qDebug() << "Register success";
    }else{
        QMessageBox::warning(this, "Register","Register failed");
        qDebug() << "Register failed!";
    }
}


void login::on_btn_login_clicked()
{
    this->get_input();
    //REQ_LOGI{"username": "ngoctu", "password": "123456"}
    QString request = "REQ_LOGI"+this->data;
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
        qDebug() <<"Login success!";
        int user_id = jsonObject.value("id").toInt();
        QJsonValue name = jsonObject.value("name");
        int age = jsonObject.value("age").toInt();
        QJsonValue phone = jsonObject.value("phone");
        QJsonValue address = jsonObject.value("address");

        User& user = User::getInstance();
        user.set_user(user_id, this->username,this->password);

        qDebug() << "userid: "+QString::number(user_id)+"; name: "+name.toString()+"; age: "+QString::number(age)+"; phone: "+phone.toString()+"; address: "+address.toString();

        this->openMainWindow();
        this->close();
    }else{
        QMessageBox::warning(this,"Log In","Account is not exist. Or username/password wrong");
    }
}

