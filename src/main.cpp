#include <QApplication>
#include <QMainWindow>
#include  <client.h>
#include "singleton.h"
#include "login.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login login;
    login.show();
    return a.exec();
}
