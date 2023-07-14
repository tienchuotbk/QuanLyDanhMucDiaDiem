#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "postscreen.h"
#include <QMainWindow>
#include <QList>
#include "post.h"
#include <QListWidget>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void post_location();
    void get_listfriend();
    void reload_infor();

private slots:
    void on_btn_post_clicked();

    void on_btn_account_clicked();

private:
    Ui::MainWindow *ui;
    QString id;
    //postscreen* posts;
    QListWidget *listfriend;

};

#endif // MAINWINDOW_H
