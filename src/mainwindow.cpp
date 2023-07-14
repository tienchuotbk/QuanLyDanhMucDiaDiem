#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "user.h"
#include "location.h"
#include "post.h"
#include "listpost.h"
#include "post.h"
#include "singleton.h"
#include <QDebug>
#include <QListWidget>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "postscreen.h"
#include "changeinfor.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->reload_infor();
    this->get_listfriend();
    //Singleton::getInstance().receiveMessages();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reload_infor(){
    User& user = User::getInstance();

    ui->label_userid->setText(QString::number(user.get_userid()));
    ui->label_username->setText(user.get_username());
}

void MainWindow::get_listfriend(){
    qDebug() << "GET friend!";
    QListWidget* listfriend = ui->listWidget;
    QString req = "GET_FRIE{\"userId\": "+QString::number(User::getInstance().get_userid())+"}";
    qDebug() << req;
    char *jsonData = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    qDebug() << jsonData;

    QByteArray jsonByteArray(jsonData);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByteArray);
    if (!jsonDoc.isNull()) {
           QJsonObject jsonObj = jsonDoc.object();
           // Kiểm tra giá trị "success"
           if (jsonObj["success"].toInt() == 1) {
               // Lấy mảng "friend"
               QJsonArray friendArray = jsonObj["friend"].toArray();

               // Tạo QListWidget và QTreeWidget
               QTreeWidget treeWidget;
               treeWidget.setHeaderLabels(QStringList() << "Key" << "Value");

               // Duyệt qua mảng "friend"
               foreach (const QJsonValue& friendValue, friendArray) {
                   // Lấy thông tin từng người bạn
                   QJsonObject friendObj = friendValue.toObject();
                   int id = friendObj["id"].toInt();
                   QString name = friendObj["name"].toString();
                   int age = friendObj["age"].toInt();
                   QString phone = friendObj["phone"].toString();
                   QString address = friendObj["address"].toString();

                   // Thêm thông tin vào QListWidget
                   QString listItem = QString("%1 (%2)\n  >%3\n  >%4\n  >%5").arg(name, "ID: "+QString::number(id),"Age:" + QString::number(age),"Phone: "+phone,"Address: "+address);

                   listfriend->addItem(listItem);

               }
               listfriend->show();
           } else {
               qDebug() << "Error: Request unsuccessful";
           }
       } else {
           qDebug() << "Error: Invalid JSON data";
       }
}



void MainWindow::on_btn_post_clicked()
{
    postscreen *post = new postscreen();
    post->show();
}


void MainWindow::on_btn_account_clicked()
{
    changeinfor *newchange = new changeinfor();
    newchange->show();
    this->reload_infor();
}

