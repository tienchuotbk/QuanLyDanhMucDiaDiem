#include "singleton.h"
#include "client.h"
#include <stdio.h> /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <QString>
#include "loginform.h"
#include <QDebug>
#include "pthread.h"
#define BUFF_SIZE 2048


Singleton::Singleton() {
    // Constructor implementation
    this->client_sock = socket(AF_INET, SOCK_STREAM, 0);
    // Step 2: Specify server address
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(5001);
    this->server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(this->client_sock, (struct sockaddr *)&this->server_addr, sizeof(struct sockaddr)) < 0)
    {
        qDebug() <<("\nError!Can not connect to sever! Client exit imediately! ");
        return ;
    } else {
        qDebug() << ("Connect success\n");
    }
//    this->f = new loginForm;
//    this->w = new  MainWindow();
//    this->f->show();
}

Singleton& Singleton::getInstance() {
    static Singleton instance;
    return instance;
}

char* Singleton::sendandrecieve(char* str) {
    printf("Send %s\n", str);
    char* temp = new char[BUFF_SIZE];
    this->bytes_sent = send(this->client_sock, str, strlen(str), 0); //Send message to server
    if (this->bytes_sent < 0) {
        perror("Error: ");
        close(this->client_sock);
        delete[] temp; // Free memory before returning
        return nullptr; // Return nullptr to indicate failure
    } else {
        qDebug() << ("Send message Ok\n");
    }

    this->bytes_received = recv(this->client_sock, temp, BUFF_SIZE - 1, 0); //Get message from server
    if (this->bytes_received < 0) {
        perror("Error: ");
        close(this->client_sock);
        delete[] temp; // Free memory before returning
        return nullptr; // Return nullptr to indicate failure
    }
    temp[this->bytes_received] = '\0';
    qDebug() << "Get receive from server:" + QString::fromUtf8(temp);
//    QString tmp = QString::fromUtf8(temp);
//    delete[] temp; // Free memory before returning
//    return tmp.toUtf8().data();
    return temp;
    delete[] temp;
}

void* Singleton::receiveMessages()
{
    char buff[BUFF_SIZE + 1];
    int bytes_received;

    while (1)
    {
        memset(buff, '\0', (strlen(buff) + 1));

        bytes_received = recv(this->client_sock, buff, BUFF_SIZE - 1, 0); // Get message from server

        if (bytes_received < 0)
        {
            perror("Error: ");
            close(client_sock);
            pthread_exit(NULL);
        }
        buff[bytes_received] = '\0';
        qDebug() << QString::fromUtf8(buff);

        // Display message from server
        qDebug() <<("-----------------------------");
        qDebug() <<  buff;
        qDebug() << ( "-----------------------------");
    }

    pthread_exit(NULL);
}

void Singleton::closeConection(){
    close(this->client_sock);
}
