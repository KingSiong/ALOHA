#include "Server.h"

Server::Server(int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, 
        std::string s_addr = "127.0.0.1", int port = 1234) {
    socket_descriptor = socket(domain, type, protocol);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1234);
    bind(socket_descriptor, (struct sockaddr*)&addr, sizeof(addr));
}

Server::~Server() {}