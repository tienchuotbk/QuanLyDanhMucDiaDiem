#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>

namespace Ui {
class mainscreen;
}

class mainscreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainscreen(QWidget *parent = nullptr);
    ~mainscreen();

private:
    Ui::mainscreen *ui;
};

#endif // MAINSCREEN_H
