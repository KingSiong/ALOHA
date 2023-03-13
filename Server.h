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

class Server {
private:
    int socket_descriptor;
    struct sockaddr_in addr;
    std::vector<Packet>packages;
public:
    Server(int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, 
        std::string s_addr = "127.0.0.1", int port = 1234);
    void start();
    void stopServerRunning(int p); 
    ~Server();
};

#endif
