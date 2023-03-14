#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <sys/socket.h>
 #include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <cstring>

class Client {
private:
    int fd;
    struct sockaddr_in seraddr;
public:
    Client(int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, 
        std::string s_addr = "127.0.0.1", int port = 1234);
    //void stopClientRunning(int p); 
    int sendPacket(std::string name,std::string msg);
    ~Client();
};

#endif
