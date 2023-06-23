#include "mainwindow.h"

#include <QApplication>
#include "socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Socket socketTest;
    socketTest.Connect();
    MainWindow w;
    w.show();
    return a.exec();
}
