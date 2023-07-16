#ifndef COMMENT_H
#define COMMENT_H

#include <QDialog>
#include <QListWidget>
namespace Ui {
class comment;
}

class comment : public QDialog
{
    Q_OBJECT

public:
    explicit comment(QString locationId,QWidget *parent = nullptr);
    ~comment();
    void set_label();

private slots:
    void on_btn_comment_clicked();

    void on_btn_viewUser_clicked();

    void on_pushButton_clicked();

private:
    Ui::comment *ui;
    QString locationId;
    QString userId;
    QListWidget* comts;
};

#endif // COMMENT_H
