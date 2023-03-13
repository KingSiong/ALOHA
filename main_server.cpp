#include <iostream>
#include "Server.h"

int main(int argc, char **argv) {
    //创建服务端和客户端
    Server server=Server();
    server.start();
    return 0;
}