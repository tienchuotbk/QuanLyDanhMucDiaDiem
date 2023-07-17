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
#include "friendinfo.h"
#include "comment.h"
#include "QThread"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->reload_infor();
    this->get_listfriend();
    this->get_liststranger();
this->general_load();
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::on_btn_item_clicked);
    connect(ui->listWidget2, &QListWidget::itemDoubleClicked, this, &MainWindow::on_btn_item_clicked);
    connect(ui->feed, &QListWidget::itemDoubleClicked, this, &MainWindow::on_feeditem_clicked);
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

                   // Thêm thông tin vào QListWidget
                   QString listItem = QString("%1 (%2)").arg(name, "ID: "+QString::number(id));

                   listfriend->addItem(listItem);

               }
               listfriend->show();

           } else {
               qDebug() << "Error: Request unsuccessful or user dont have friend";
           }
       } else {
           qDebug() << "Error: Invalid JSON data";
       }
}

void MainWindow::get_liststranger(){
    QListWidget* listfriend = ui->listWidget2;
    //GET_STRG
    //{"success": 1, "stranger": [{"id": 3, "name": "Nguyen Duc Phuc", "age": 25, "phone": "0123895654", "address": "Sai Gon"}]}
    QString req = "GET_STRG{\"userId\": "+QString::number(User::getInstance().get_userid())+"}";
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
               QJsonArray friendArray = jsonObj["stranger"].toArray();

               // Tạo QListWidget và QTreeWidget
               QTreeWidget treeWidget;
               treeWidget.setHeaderLabels(QStringList() << "Key" << "Value");

               // Duyệt qua mảng "friend"
               foreach (const QJsonValue& friendValue, friendArray) {
                   // Lấy thông tin từng người bạn
                   QJsonObject friendObj = friendValue.toObject();
                   int id = friendObj["id"].toInt();
                   QString name = friendObj["name"].toString();

                   // Thêm thông tin vào QListWidget
                   QString listItem = QString("%1 (%2)").arg(name, "ID: "+QString::number(id));

                   listfriend->addItem(listItem);

               }
               listfriend->show();

           } else {
               qDebug() << "Error: Request unsuccessful or user dont have friend";
           }
       } else {
           qDebug() << "Error: Invalid JSON data";
       }
}

void MainWindow::on_btn_item_clicked(QListWidgetItem *item){
    qDebug() << QString(item->text());
    QString listItem = item->text();
    int idStartIndex = listItem.lastIndexOf(": ") + 1;
    QString extractedId = listItem.mid(idStartIndex).trimmed();
    extractedId.remove(QRegExp("[^0-9]"));
    qDebug() << extractedId;
    friendinfo *friendi = new friendinfo(extractedId);
    friendi->exec();
    delete friendi;
}

void MainWindow::on_feeditem_clicked(QListWidgetItem *item){
    qDebug() << QString(item->text());
    QString str = item->text();
    QRegularExpression regex("\\n\\((\\d+)\\)");

    QRegularExpressionMatch match = regex.match(str);

    // Check if the match is valid and extract the captured number
    if (match.hasMatch()) {
        QString number = match.captured(1);
        qDebug() << "Extracted number:" << number;
        comment *comt = new comment(number);
        comt->exec();
        delete comt;
    } else {
        qDebug() << "No match found.";
    }
}


void MainWindow::on_btn_post_clicked()
{
    postscreen *post = new postscreen();
    post->exec();
    delete post;
}


void MainWindow::on_btn_account_clicked()
{
    changeinfor *newchange = new changeinfor();
    newchange->show();
    this->reload_infor();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    qDebug() <<index;
    QString req = "FIND_LOC{\"userId\": "+QString::number(User::getInstance().get_userid())+", \"type\": "+QString::number(index)+", \"value\": \"\"}";
    qDebug() << req;
    char *jsonDatat = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    int jsonDataLength = strlen(jsonDatat);

    char *jsonData = new char[jsonDataLength + 1];
    memcpy(jsonData, jsonDatat, jsonDataLength);
    jsonData[jsonDataLength] = '\0';
    if (jsonData) {
        qDebug() << "Raw JSON Data:" << jsonData;
        int jsonDataLength = strlen(jsonData);
        qDebug() << "JSON Data Length:" << jsonDataLength;
        // Check for the presence of the closing curly brace
        if (jsonDataLength > 0 && jsonData[jsonDataLength - 1] == '}') {
            qDebug() << "JSON Data is Properly Terminated";
        } else {
            qDebug() << "JSON Data is NOT Properly Terminated";
        }
    } else {
        qDebug() << "jsonData is NULL";
    }

    // Convert to QByteArray and parse as JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parsing Error:" << parseError.errorString();
    } else {
        qDebug() << "JSON Parsing Successful";
        // Do further processing with the JSON data
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray array = jsonObj["location"].toArray();
        this->load_notfeed(array);
    }

    // Don't forget to clean up the dynamically allocated jsonDataNullTerminated
    delete[] jsonData;
}

void MainWindow::load_feed(QJsonArray ar)
{
    QVector<QString> values = {"ALL","School", "Coffe", "Restaurant", "Park", "Mall", "Market", "Hospital", "Others"};
    QListWidget* feed = ui->feed;
    feed->clear();
    User &user = User::getInstance();
    foreach (const QJsonValue& item, ar) {
        // Lấy thông tin
        //"userId": 2, "userName": "Nguyen Ngoc Tu", "locationId": 5, "locationName": "Bach Mai", "type": 7, "locationAdd": "15 Giai Phong, Hai Ba Trung, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 4, "locationName": "Dong Xuan", "type": 6, "locationAdd": "Hang Buom, Hoan Kiem, Ha Noi"}, {"userId": 2, "userName": "Nguyen Ngoc Tu", "locationId": 3, "locationName": "Lau Phan", "type": 3, "locationAdd": "15 Pho Hue, Hai Ba Trung, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 2, "locationName": "Gongtea", "type": 2, "locationAdd": "23 Vu Trong Phung, Thanh Xuan, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 1, "locationName": "Dai hoc Bach Khoa Ha Noi", "type": 1, "locationAdd": "1 Dai Co Viet, Hai Ba Trung, Ha Noi"
        QJsonObject itemObj = item.toObject();
        int id = itemObj["userId"].toInt();
        QString name = itemObj["userName"].toString();
        int locationId = itemObj["locationId"].toInt();
        QString locationName = itemObj["locationName"].toString();
        int type = itemObj["type"].toInt();
        QString address = itemObj["address"].toString();

        QString listItem;

        // Thêm thông tin vào QListWidget
        if(user.get_userid() == id){
            listItem = QString("\n(%1). You shared a location\n  >Name : %2\n    >Category: %3\n      >Address: %4\n        >( Click to view comment)\n__________________________________________________________________________________________________").arg(
                    QString::number(locationId), locationName, values.at(type), address);
        }else{
            listItem = QString("\n(%1). %2 (%3) shared a location\n  >Name : %4\n    >Category: %5\n      >Address: %6\n        >( Click to view comment)\n__________________________________________________________________________________________________").arg(
                    QString::number(locationId), name, "ID: "+QString::number(id), locationName, values.at(type), address);
        }
        feed->addItem(listItem);
    }
    feed->show();
}

void MainWindow::load_notfeed(QJsonArray ar){
    QVector<QString> values = {"ALL","School", "Coffe", "Restaurant", "Park", "Mall", "Market", "Hospital", "Others"};
    QListWidget* feed = ui->feed;
    feed->clear();
    foreach (const QJsonValue& item, ar) {
        // Lấy thông tin
        //"userId": 2, "userName": "Nguyen Ngoc Tu", "locationId": 5, "locationName": "Bach Mai", "type": 7, "locationAdd": "15 Giai Phong, Hai Ba Trung, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 4, "locationName": "Dong Xuan", "type": 6, "locationAdd": "Hang Buom, Hoan Kiem, Ha Noi"}, {"userId": 2, "userName": "Nguyen Ngoc Tu", "locationId": 3, "locationName": "Lau Phan", "type": 3, "locationAdd": "15 Pho Hue, Hai Ba Trung, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 2, "locationName": "Gongtea", "type": 2, "locationAdd": "23 Vu Trong Phung, Thanh Xuan, Ha Noi"}, {"userId": 1, "userName": "Tien Chuot", "locationId": 1, "locationName": "Dai hoc Bach Khoa Ha Noi", "type": 1, "locationAdd": "1 Dai Co Viet, Hai Ba Trung, Ha Noi"
        QJsonObject itemObj = item.toObject();
        QString name = itemObj["userName"].toString();
        int locationId = itemObj["id"].toInt();
        QString locationName = itemObj["name"].toString();
        int type = itemObj["type"].toInt();
        QString address = itemObj["address"].toString();

        QString listItem;

        // Thêm thông tin vào QListWidget

        listItem = QString("\n(%1) (%2) %3 at %4\n     >( Click to view comment)\n__________________________________________________________________________________________________").arg(
                    QString::number(locationId), values.at(type), locationName, address);
        feed->addItem(listItem);
    }
    feed->show();
}

void MainWindow::general_load(){
    User &user = User::getInstance();
    QString req = "GET_FEED{\"userId\": "+QString::number(user.get_userid())+"}";
    qDebug() << req;
    char* jsonData = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
//    int jsonDataLength = strlen(jsonDatat);

//    char* jsonData = new char[jsonDataLength];
//    memcpy(jsonData, jsonDatat, jsonDataLength);
//    jsonData[jsonDataLength] = '\0'; // Null-terminate the received data

    if (strlen(jsonData)!=0) {
        qDebug() << "Raw JSON Data:" << jsonData;
        int jsonDataLength = strlen(jsonData);
        qDebug() << "JSON Data Length:" << jsonDataLength;
        if (jsonDataLength > 0 && jsonData[jsonDataLength - 1] == '}') {
            qDebug() << "JSON Data is Properly Terminated";
        } else {
            qDebug() << "JSON Data is NOT Properly Terminated";
             qDebug() << jsonData[jsonDataLength - 1];
             qDebug() << jsonData;
        }
    } else {
        qDebug() << "jsonData is NULL";
    }

    // Convert to QByteArray and parse as JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parsing Error:" << parseError.errorString();
        qDebug() << jsonDoc;
    } else {
        qDebug() << "JSON Parsing Successful";
        // Do further processing with the JSON data
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray array = jsonObj["locationShare"].toArray();
        this->load_feed(array);
    }

    // Don't forget to clean up the dynamically allocated jsonData
    //delete[] jsonData;

}

void MainWindow::on_btn_reload_clicked()
{

    ui->comboBox->setCurrentIndex(0);
    ui->input_search->setText("");
    ui->feed->clear();
    ui->listWidget->clear();
    ui->listWidget2->clear();

    this->get_listfriend();
    this->get_liststranger();
    this->general_load();
}


void MainWindow::on_btn_search_clicked()
{
    int index =  ui->comboBox->currentIndex();
    QString value = ui->input_search->text();
    QString req = "FIND_LOC{\"userId\": "+QString::number(User::getInstance().get_userid())+", \"type\": "+QString::number(index)+", \"value\": \""+value+"\"}";
    qDebug() << req;
    char *jsonDatat = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    int jsonDataLength = strlen(jsonDatat);

    char *jsonData = new char[jsonDataLength + 1];
    memcpy(jsonData, jsonDatat, jsonDataLength);
    jsonData[jsonDataLength] = '\0';
    if (jsonData) {
        qDebug() << "Raw JSON Data:" << jsonData;
        int jsonDataLength = strlen(jsonData);
        qDebug() << "JSON Data Length:" << jsonDataLength;
        // Check for the presence of the closing curly brace
        if (jsonDataLength > 0 && jsonData[jsonDataLength - 1] == '}') {
            qDebug() << "JSON Data is Properly Terminated";
        } else {
            qDebug() << "JSON Data is NOT Properly Terminated";
        }
    } else {
        qDebug() << "jsonData is NULL";
    }

    // Convert to QByteArray and parse as JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parsing Error:" << parseError.errorString();
    } else {
        qDebug() << "JSON Parsing Successful";
        // Do further processing with the JSON data
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray array = jsonObj["location"].toArray();
        this->load_notfeed(array);
    }

    // Don't forget to clean up the dynamically allocated jsonDataNullTerminated
    delete[] jsonData;

}


void MainWindow::on_btn_location_save_clicked()
{
    QString req = "GET_SLOC{\"userId\": "+QString::number(User::getInstance().get_userid())+"}";
    qDebug() << req;
    char *jsonDatat = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    int jsonDataLength = strlen(jsonDatat);

    char *jsonData = new char[jsonDataLength + 1];
    memcpy(jsonData, jsonDatat, jsonDataLength);
    jsonData[jsonDataLength] = '\0';
    if (jsonData) {
        qDebug() << "Raw JSON Data:" << jsonData;
        int jsonDataLength = strlen(jsonData);
        qDebug() << "JSON Data Length:" << jsonDataLength;
        // Check for the presence of the closing curly brace
        if (jsonDataLength > 0 && jsonData[jsonDataLength - 1] == '}') {
            qDebug() << "JSON Data is Properly Terminated";
        } else {
            qDebug() << "JSON Data is NOT Properly Terminated";
        }
    } else {
        qDebug() << "jsonData is NULL";
    }

    // Convert to QByteArray and parse as JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parsing Error:" << parseError.errorString();
    } else {
        qDebug() << "JSON Parsing Successful";
        // Do further processing with the JSON data
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray array = jsonObj["saveLocation"].toArray();
        this->load_notfeed(array);
    }

    // Don't forget to clean up the dynamically allocated jsonDataNullTerminated
    delete[] jsonData;
}


void MainWindow::on_pushButton_clicked()
{
    QString req = "GET_RECO{\"userId\": "+QString::number(User::getInstance().get_userid())+"}";
    qDebug() << req;
    char *jsonDatat = Singleton::getInstance().sendandrecieve(req.toUtf8().data());
    int jsonDataLength = strlen(jsonDatat);

    char *jsonData = new char[jsonDataLength + 1];
    memcpy(jsonData, jsonDatat, jsonDataLength);
    jsonData[jsonDataLength] = '\0';
    if (jsonData) {
        qDebug() << "Raw JSON Data:" << jsonData;
        int jsonDataLength = strlen(jsonData);
        qDebug() << "JSON Data Length:" << jsonDataLength;
        // Check for the presence of the closing curly brace
        if (jsonDataLength > 0 && jsonData[jsonDataLength - 1] == '}') {
            qDebug() << "JSON Data is Properly Terminated";
        } else {
            qDebug() << "JSON Data is NOT Properly Terminated";
        }
    } else {
        qDebug() << "jsonData is NULL";
    }

    // Convert to QByteArray and parse as JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parsing Error:" << parseError.errorString();
    } else {
        qDebug() << "JSON Parsing Successful";
        // Do further processing with the JSON data
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray array = jsonObj["location"].toArray();
        this->load_notfeed(array);
    }

    // Don't forget to clean up the dynamically allocated jsonDataNullTerminated
    delete[] jsonData;

}

