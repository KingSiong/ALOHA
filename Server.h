#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

class Server {
private:
    int socket_descriptor;
    struct sockaddr_in addr;
public:
    Server(int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, 
        std::string s_addr = "127.0.0.1", int port = 1234);
    ~Server();
};

#endif