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
#include <stdio.h>
using namespace std;
#define BUFF_SIZE 1024
#include "loginform.h"
#include <QApplication>
client::client()
{

}
client::client(int port, char* ip){
//    QApplication a();
//    loginForm *f= new loginForm;
//    f->show();
    // Step 1: Construct socket
    this->client_sock = socket(AF_INET, SOCK_STREAM, 0);
    // Step 2: Specify server address
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(port);
    this->server_addr.sin_addr.s_addr = inet_addr(ip);
    printf("Port:%d, IP:%s\n", port, ip);

    // Step 3: Request to connect server
    if (connect(this->client_sock, (struct sockaddr *)&this->server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return ;
    } else {
        printf("OOk\n");
    }
    printf("Enter username:(Press Enter to exit):\n");

    while (true)
    {
        this->buff="Hello";


        char temp[BUFF_SIZE];
        printf("Gui ne/n");
        this->bytes_sent = send(this->client_sock, this->buff, strlen(this->buff), 0); //Send message to server
        if (this->bytes_sent < 0)
        {
            perror("Error: ");
            close(this->client_sock);
            return ;
        } else {
            printf("Send message Ok\n");
        }

        this->bytes_received = recv(this->client_sock, temp, BUFF_SIZE - 1, 0); //Get message from server
        this->buff  =  temp;
        if (this->bytes_received < 0)
        {
            perror("Error: ");
            close(this->client_sock);
            return ;
        }
        this->buff[this->bytes_received] = '\0';
        // Dislay message from server
        printf("%s\n", "-----------------------------");
        printf("%s\n", this->buff);
        printf("%s\n", "-----------------------------");
        break;
    }
}
void client::closeClient(){
    close(this->client_sock);
}
