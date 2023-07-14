#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

class client
{
public:
    client();
    client(int port, char* string);
    void closeClient();
private:
    int client_sock;
    char* buff;
    struct sockaddr_in server_addr;
    int msg_len, bytes_sent, bytes_received;


};

#endif // CLIENT_H
