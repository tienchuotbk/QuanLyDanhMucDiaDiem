#include "server.h"
#include <QApplication>
#include <stdio.h> /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#define BUFF_SIZE 1024
#define MAX_USERNAME_LENGTH 25
#define MAX_PASSWORD_LENGTH 25
#define BACKLOG 20 /* Number of allowed connections */
server::server(){}

server::server(int port)
{

    if ((this->listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    { /* calls socket() */
        perror("\nError: ");
        return ;
    }
    bzero(&this->serverAdd, sizeof(this->serverAdd));
    this->serverAdd.sin_family = AF_INET;
    this->serverAdd.sin_port = htons(port);
    this->serverAdd.sin_addr.s_addr = htonl(INADDR_ANY); /* INADDR_ANY puts your IP address automatically */

    if (bind(this->listenfd, (struct sockaddr *)&this->serverAdd, sizeof(this->serverAdd)) == -1)
    {
        perror("\nError: ");
        return ;
    }

    if (listen(this->listenfd, BACKLOG) == -1)
    {
        perror("\nError: ");
        return ;
    }

    this->sin_size = sizeof(struct sockaddr_in);
    this->clientAdd = (sockaddr_in*)malloc(this->sin_size);
    // Step 3: Communicate with clients

    while (1)
    {
        this->connfd = (int*)malloc(sizeof(int));
//        printf("server is listennning at port %s\n", port);
        if ((*this->connfd = accept(this->listenfd, (struct sockaddr *)this->clientAdd, &this->sin_size)) == -1)
            perror("\nError: ");
        printf("You got a connection from %s\n", inet_ntoa(this->clientAdd->sin_addr)); /* prints client's IP */

        /* For each client, spawns a thread, and the thread handles the new client */
        pthread_create(&this->tid, NULL, &(this->echo), this->connfd);
    }
}
void* server::echo(void* arg){
    int connfd;
    char temp[BUFF_SIZE];
    int bytes_sent, bytes_received;
    char buff[BUFF_SIZE + 1];
    printf("Newwww thread creaated\n");

    connfd = *((int *)arg);
    free(arg);
    pthread_detach(pthread_self());

    while (1)
    {
        bytes_received = recv(connfd, buff, BUFF_SIZE - 1, 0);

        if (bytes_received < 0)
            perror("\nError: ");
        else
        {
            buff[bytes_received] = '\0';
            printf("%s\n", buff);
        }
    }
    printf("Client closed connection\n");
    close(connfd);
}
