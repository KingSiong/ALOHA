#include <iostream>
#include "Client.h"

int main(int argc, char **argv) {
    //创建服务端和客户端
    Client client=Client();
    //客户端发送消息
    client.sendPacket("xvmao","hello,world!");
    client.sendPacket("jingsong","hello,world!");
    client.sendPacket("sunlu","hello,world!");

    while(1);//等待服务端接收信息
    return 0;
}