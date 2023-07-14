#include "loginform.h"
#include <QDebug>
#include "singleton.h"
#include <QByteArray>
#include  "string.h"
#include <QMessageBox>
#include "loginscreen.h"

#include "ui_loginform.h"
loginForm::loginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginForm)
{
    ui->setupUi(this);
}

loginForm::~loginForm()
{
    delete ui;
}

//void loginForm::on_pushButton_clicked()
//{
//    Singleton& clients = Singleton::getInstance();
//    QByteArray byteName = this->username.toUtf8();
//    char* message = (char*)malloc(sizeof(char*));
//    //loggin
//    //qDebug()<<(this->username);
//    printf("Butoon clicked\n%s!\n", name);
//    message = clients.sendandrecieve(name);
//    printf("MMesssage =%s\n", message);

//    if(strcmp(message, "Ok") == 0){
//        printf("Cloose\n");
//        clients.f->hide();
//        clients.w->show();
//    }
//    return;
//}
void loginForm::getInput(){
    this->username = ui->user_input->text();
    this->password = ui->pwd_input->text();
}

void loginForm::closeEvent(QCloseEvent* event){
    Singleton& clients = Singleton::getInstance();
    clients.closeConection();
}


void loginForm::on_register_btn_clicked()
{
    this->getInput();
    QMessageBox::information(this,"Register","Register success!");
    //not success
    //QMessageBox::warning(this,"Register","Register failed!");
}


void loginForm::on_login_btn_clicked()
{
    this->getInput();
    //login success
    MainWindow main;
    main.setModal(true);
    //login failed
    //QMessageBox::warning(this,"Log In","User name or password failed!");
}

