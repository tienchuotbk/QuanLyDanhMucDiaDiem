#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include <QDialog>
#include "loginform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Loginscreen : public QDialog
{
    Q_OBJECT

public:
    Loginscreen(QWidget *parent = nullptr);
    ~Loginscreen();
    void getInput();
    void on_register_btn_clicked();
    void on_login_btn_clicked();


private:
    QString username;
    QString password;
};
#endif // LOGINSCREEN_H
