#ifndef SINGLETON_H
#define SINGLETON_H
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <stdio.h> /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;
#define BUFF_SIZE 1024

class Singleton {
public:
    // Method to get the singleton instance
    static Singleton& getInstance();
    char* sendandrecieve(char *str);
    void closeConection();
    void *receiveMessages();
    // Other public member functions

private:
    // Private constructor to prevent instantiation
    Singleton();
    int client_sock;
    char* buff;
    struct sockaddr_in server_addr;
    int msg_len, bytes_sent, bytes_received;

    // Private copy constructor and assignment operator to prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

#endif // SINGLETON_H
