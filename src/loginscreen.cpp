#include "loginscreen.h"
#include "QMessageBox"
#include "ui_loginform.h"

Loginscreen::Loginscreen(QWidget *parent): QDialog(parent), ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}


void Loginscreen::getInput(){
    this->username = ui->user_input_2->text();
    this->password = ui->pwd_input_2->text();
}

void Loginscreen::on_register_btn_clicked()
{
    this->getInput();
    QMessageBox::information(this,"Register","Register success!");
    //not success
    //QMessageBox::warning(this,"Register","Register failed!");
}


void Loginscreen::on_login_btn_clicked()
{
    this->getInput();
    //login success
    //MainWindow main;
    //main.setModal(true);
    //login failed
    //QMessageBox::warning(this,"Log In","User name or password failed!");
}
