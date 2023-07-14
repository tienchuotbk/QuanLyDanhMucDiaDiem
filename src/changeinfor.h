#ifndef CHANGEINFOR_H
#define CHANGEINFOR_H

#include <QDialog>

namespace Ui {
class changeinfor;
}

class changeinfor : public QDialog
{
    Q_OBJECT

public:
    explicit changeinfor(QWidget *parent = nullptr);
    ~changeinfor();

    void get_infor();

private slots:
    void on_btn_save_clicked();

private:
    Ui::changeinfor *ui;
};

#endif // CHANGEINFOR_H
