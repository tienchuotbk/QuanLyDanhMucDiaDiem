#ifndef FRIENDINFO_H
#define FRIENDINFO_H
#include <QString>
#include <QDialog>

namespace Ui {
class friendinfo;
}

class friendinfo : public QDialog
{
    Q_OBJECT

public:
    explicit friendinfo(QString &id,QWidget *parent = nullptr);
    ~friendinfo();
    void set_infor();

private slots:
    void on_btn_follow_clicked();

private:
    Ui::friendinfo *ui;
    QString id;
};

#endif // FRIENDINFO_H
