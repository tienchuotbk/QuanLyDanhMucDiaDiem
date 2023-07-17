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
    void load_feed(QJsonArray ar);
    void general_load();
    void load_notfeed(QJsonArray ar);
    void get_liststranger();


private slots:
    void on_btn_post_clicked();
    void on_btn_account_clicked();
    void on_btn_item_clicked(QListWidgetItem *item);
    void on_comboBox_currentIndexChanged(int index);

    void on_btn_reload_clicked();

    void on_btn_search_clicked();
    void on_feeditem_clicked(QListWidgetItem *item);

    void on_btn_location_save_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString id;
    //postscreen* posts;
    QListWidget *listfriend;
    QListWidget *feed;

};

#endif // MAINWINDOW_H
