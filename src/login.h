#ifndef LOGIN_H
#define LOGIN_H
#include"mainwindow.h"
#include <QDialog>
#include "singleton.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void get_input();


private slots:
    void on_btn_register_clicked();
    void on_btn_login_clicked();
    void openMainWindow();
private:
    Ui::login *ui;
    QString username;
    QString password;
    MainWindow* mainWindow;
    QString data;
};

#endif // LOGIN_H
