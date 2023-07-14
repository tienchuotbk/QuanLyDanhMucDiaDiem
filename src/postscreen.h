#ifndef POSTSCREEN_H
#define POSTSCREEN_H
#include <QString>
#include <QDialog>
#include "comment.h"

namespace Ui {
class postscreen;
}

class postscreen : public QDialog
{
    Q_OBJECT

public:
    explicit postscreen(QWidget *parent = nullptr);
    ~postscreen();
    void collect_input();

private slots:
    void on_btn_post_clicked();

private:
    Ui::postscreen *ui;
    QString location_name;
    QString address;
    int type;
};

#endif // POSTSCREEN_H
