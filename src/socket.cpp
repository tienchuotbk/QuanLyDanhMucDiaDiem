#include "socket.h"

Socket::Socket(QObject *parent)
    : QObject{parent}
{

}

void Socket::Connect(){
    //connect to socket
    socket = new QTcpSocket(this);
    socket->connectToHost("google.com", 80);

    if(socket->waitForConnected(3000)){
        qDebug() << "Connected!";
        socket->close();
    } else
        {
            qDebug() << "Not connected!";
        }

}
