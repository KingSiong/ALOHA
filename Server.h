#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Package.h"
#include <string>
#include <unistd.h>
#include <cstring>
#include <signal.h>
#include <vector>
#include <iostream>

#define MAX_LINK 5
#define MAX_LEN 1024

class Server {
private:
    int socket_fd;
    struct sockaddr_in addr;
    std::vector<Packet>packages;
public:
    Server(int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, 
        std::string s_addr = "127.0.0.1", int port = 1234);
    void start();
    int receive_package(int connect_fd);
    int feedback(int connect_fd);
    void handle_package(char *message);
    void stopServerRunning(int p); 
    ~Server();
};

#endif
